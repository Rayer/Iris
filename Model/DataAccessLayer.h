/**
 * Project Untitled
 */


#ifndef _DATAACCESSLAYER_H
#define _DATAACCESSLAYER_H

class DataAccessLayer {
public: 
    
    /**
     * @param id
     */
    Space get_space(long id);
    
    /**
     * @param name
     */
    Space get_space(string name);
    
    List<Space> get_space_list();
};

#endif //_DATAACCESSLAYER_H