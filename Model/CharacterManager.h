/**
 * Project Untitled
 */


#ifndef _CHARACTERMANAGER_H
#define _CHARACTERMANAGER_H

class CharacterManager {
public: 
    
    /**
     * @param template
     */
    Character create_character(CharacterTemplate template);
    
    /**
     * @param id
     */
    Character get_character(string id);
    
    /**
     * @param id
     */
    Character remove_character(string id);
};

#endif //_CHARACTERMANAGER_H