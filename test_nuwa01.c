/*
 * Used when an allocation is about to fail under memory pressure. This
 * potentially hurts the reliability of high-order allocations when under
 * intense memory pressure but failed atomic allocations should be easier
 * to recover from than an OOM.
 *
 * If @force is true, try to unreserve a pageblock even though highatomic
 * pageblock is exhausted.
 */
static bool unreserve_highatomic_pageblock(const struct alloc_context *ac,
						bool force)
{
	struct zonelist *zonelist = ac->zonelist;
	unsigned long flags;
	struct zoneref *z;
	struct zone *zone;
	struct page *page;
	int order;
	bool ret;

	for_each_zone_zonelist_nodemask(zone, z, zonelist, ac->highest_zoneidx,
								ac->nodemask) {
		/*
		 * Preserve at least one pageblock unless memory pressure
		 * is really high.
		 */

		if (!force && zone->nr_reserved_highatomic <=
					pageblock_nr_pages)
			continue;

		spin_lock_irqsave(&zone->lock, flags);
		for (order = 0; order < MAX_ORDER; order++) {
			struct free_area *area = &(zone->free_area[order]);

			page = get_page_from_free_area(area, MIGRATE_HIGHATOMIC);
			if (!page)
				continue;

			/*
			 * In page freeing path, migratetype change is racy so
			 * we can counter several free pages in a pageblock
			 * in this loop although we changed the pageblock type
			 * from highatomic to ac->migratetype. So we should
			 * adjust the count once.
			 */
			if (is_migrate_highatomic_page(page)) {
				/*
				 * It should never happen but changes to
				 * locking could inadvertently allow a per-cpu
				 * drain to add pages to MIGRATE_HIGHATOMIC
				 * while unreserving so be safe and watch for
				 * underflows.
				 */

				zone->nr_reserved_highatomic -= min(
						pageblock_nr_pages,
						zone->nr_reserved_highatomic);
			}

			/*
			 * Convert to ac->migratetype and avoid the normal
			 * pageblock stealing heuristics. Minimally, the caller
			 * is doing the work and needs the pages. More
			 * importantly, if the block was always converted to
			 * MIGRATE_UNMOVABLE or another type then the number
			 * of pageblocks that cannot be completely freed
			 * may increase.
			 */
			set_pageblock_migratetype(page, ac->migratetype);
			ret = move_freepages_block(zone, page, ac->migratetype,
									NULL);
			if (ret) {
				spin_unlock_irqrestore(&zone->lock, flags);
				return ret;
			}
		}
		spin_unlock_irqrestore(&zone->lock, flags);
	}

	return false;
}
