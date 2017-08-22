/**
 * Project Untitled
 */


#ifndef _INVENTORYMANAGELAYER_H
#define _INVENTORYMANAGELAYER_H

class InventoryManageLayer {
public: 
    
    /**
     * @param id
     */
    Inventory get_inventory(long id);
    
    /**
     * @param character
     */
    Inventory get_inventory(Character character);
    
    /**
     * @param inventory
     * @param item
     * @param num
     */
    void transit_item(Inventory inventory, Item item, Num num);
};

#endif //_INVENTORYMANAGELAYER_H