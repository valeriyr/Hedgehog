
-- Ground tiles with water borders
--
-- 		1 --- 2 --- 3
-- 		|     |     |
-- 		4 --- 5 --- 6
-- 		|     |     |
--		7 --- 8 --- 9

SurfaceItemsCache:regSurfaceItem(1, ISurfaceItemsCache.NotAvailable)
SurfaceItemsCache:regSurfaceItem(2, ISurfaceItemsCache.NotAvailable)
SurfaceItemsCache:regSurfaceItem(3, ISurfaceItemsCache.NotAvailable)
SurfaceItemsCache:regSurfaceItem(4, ISurfaceItemsCache.NotAvailable)
SurfaceItemsCache:regSurfaceItem(5, ISurfaceItemsCache.Ground)
SurfaceItemsCache:regSurfaceItem(6, ISurfaceItemsCache.NotAvailable)
SurfaceItemsCache:regSurfaceItem(7, ISurfaceItemsCache.NotAvailable)
SurfaceItemsCache:regSurfaceItem(8, ISurfaceItemsCache.NotAvailable)
SurfaceItemsCache:regSurfaceItem(9, ISurfaceItemsCache.NotAvailable)

-- Water tiles

SurfaceItemsCache:regSurfaceItem(101, ISurfaceItemsCache.Water)

-- Default surface item

SurfaceItemsCache:setDefaultSurfaceItem(5)

SystemMessenger:printMessage(IMessenger.Info, QString("Surface items has loaded."))