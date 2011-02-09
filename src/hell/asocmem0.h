#ifndef HELL_ASOCMEM0_H
#define HELL_ASOCMEM0_H


#include "support/alarm.h"
#include "support/count_ptr.hpp"
#include "support/signalslot.hpp"


#include <string>
#include <map>
#include <list>



namespace hell {




class asoc_mem0
{
public:
    asoc_mem0();
    //virtual ~asoc_mem0();


    void begin_scope (void);
    void end_scope   (void);

    std::string read_var   (const std::string& var_name);
    void        write_var  (const std::string& var_name, const std::string& var_value);
    void        declare_var(const std::string& var_name, const std::string& var_value);




    mtk::Signal<const mtk::Alarm&>                 signal_error;
    mtk::Signal<const std::string&, std::string&>   signal_assign_to;









private:


    class scope
    {

        public:
            std::map<std::string, mtk::CountPtr<std::string> >  local_map_name2ref;
            std::map<std::string, mtk::CountPtr<std::string> >  inherited_map_name2ref;

            void add2inherited(const scope& scope2add);

            friend std::ostream& operator<< (std::ostream& os, const scope& sco);

    };

    scope               current_scope;
    std::list <scope>   scope_stack;

    mtk::CountPtr<std::string> find_ref_from_var_name (const std::string& var_name);


    friend std::ostream& operator<< (std::ostream& os, const asoc_mem0& mem);
    friend std::ostream& operator<< (std::ostream& os, const asoc_mem0::scope& sco);

};


};  //namespace hell {

#endif // HELL_ASOCMEM0_H

