/**
 * Project Untitled
 */


#ifndef _CHARACTER_H
#define _CHARACTER_H

class Character {
public: 
    
    Inventory get_inventory();
    
    Statistics get_statistics();
    
    Actions get_actions();
    
    CharacterSpec get_identity();
};

#endif //_CHARACTER_H