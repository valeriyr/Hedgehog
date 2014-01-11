
-- Ground tiles with water borders
--
-- 		1 --- 2 --- 3
-- 		|     |     |
-- 		4 --- 5 --- 6
-- 		|     |     |
--		7 --- 8 --- 9

SurfaceItemsCache:regSurfaceItem(1, TerrainMapItem.NotAvailable)
SurfaceItemsCache:regSurfaceItem(2, TerrainMapItem.NotAvailable)
SurfaceItemsCache:regSurfaceItem(3, TerrainMapItem.NotAvailable)
SurfaceItemsCache:regSurfaceItem(4, TerrainMapItem.NotAvailable)
SurfaceItemsCache:regSurfaceItem(5, TerrainMapItem.Ground)
SurfaceItemsCache:regSurfaceItem(6, TerrainMapItem.NotAvailable)
SurfaceItemsCache:regSurfaceItem(7, TerrainMapItem.NotAvailable)
SurfaceItemsCache:regSurfaceItem(8, TerrainMapItem.NotAvailable)
SurfaceItemsCache:regSurfaceItem(9, TerrainMapItem.NotAvailable)

-- Water tiles

SurfaceItemsCache:regSurfaceItem(101, TerrainMapItem.Water)

-- Default surface item

SurfaceItemsCache:setDefaultSurfaceItem(5)

-- End script message

SystemMessenger:printMessage(IMessenger.Info, QString("Surface items has loaded."))