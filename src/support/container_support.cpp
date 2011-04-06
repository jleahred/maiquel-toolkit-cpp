#include "container_support.h"

#include <map>

#include "alarm.h"


namespace mtk {

    namespace internal_for_containers
    {
        bool                                                     __cleaned__      = false;
        int*                                                     __preg_counter__ =0;
        std::map<int, int /*last registered modif on map*/ >*    __pmreg_counter__=0;
        
        
		int& GetRegCounter(void) {
			if (__preg_counter__ == 0)
				__preg_counter__ = new int(0);
			return *__preg_counter__;
		}
		std::map<int, int>&  GetMapRegCounter(void) {
            if(__pmreg_counter__ == 0)
                __pmreg_counter__ = new std::map<int, int>;
            return *__pmreg_counter__;
        }


        int      register_container(bool is_empty)
        {
			int& regCounter = GetRegCounter();
            ++regCounter;
            GetMapRegCounter()[regCounter] = (is_empty ? 0 : 1);
            return regCounter;
        }

        void   register_container_size_change(int reg_code)
        {
            if (GetMapRegCounter().find(reg_code) == GetMapRegCounter().end())
                throw mtk::Alarm(MTK_HERE, "containersupport", "container is not registered", mtk::alPriorError);
            else
                GetMapRegCounter()[reg_code] = GetMapRegCounter()[reg_code]+1;
        }

        int  get_registered_container_last_size_change(int reg_code)
        {
            if (GetMapRegCounter().find(reg_code) == GetMapRegCounter().end())
                throw mtk::Alarm(MTK_HERE, "containersupport", "container is not registered", mtk::alPriorError);
            else
                return GetMapRegCounter()[reg_code];
        }

        bool     is_registered_container(int reg_code)
        {
            if (GetMapRegCounter().find(reg_code) != GetMapRegCounter().end())
                return true;
            else
                return false;
        }

        void     unregister_container(int reg_code)
        {
            if (__cleaned__)
                return;
            
            if (GetMapRegCounter().find(reg_code) == GetMapRegCounter().end())
                throw mtk::Alarm(MTK_HERE, "containersupport", "container is not registered", mtk::alPriorError);
            else
                GetMapRegCounter().erase(reg_code);
        }


//		esto es un truco delicado
//        static struct release {
//            ~release() {
//                if (__pmreg_counter__ != 0)
//                {
//                    delete __pmreg_counter__;
//                    __pmreg_counter__ = 0;
//                }
//				if (__preg_counter__ != 0)
//				{
//					delete __preg_counter__;
//					__preg_counter__ = 0;
//				}
//            };
//        } r;


    };  //  namespace internal_for_containers

    void __internal_containersupport_nevercall_me____release_on_exit(void)
    {
//        int*                                                     __preg_counter__ =0;
//        std::map<int, int /*last registered modif on map*/ >*    __pmreg_counter__=0;
        internal_for_containers::__cleaned__ = true;
        delete internal_for_containers::__preg_counter__;
        delete internal_for_containers::__pmreg_counter__;
    }


};   //  end namespace mtk


