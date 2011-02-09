#ifndef __container_support__
#define __container_support__



namespace mtk {

    namespace internal_for_containers
    {
        int         register_container(bool is_empty);

        void        register_container_size_change(int reg_code);

        int         get_registered_container_last_size_change(int reg_code);


        bool        is_registered_container(int reg_code);

        void        unregister_container(int reg_code);


    };  //  namespace internal_for_containers



void __internal_containersupport_nevercall_me____release_on_exit(void);
#define RELEASE__internal_containersupport_nevercall_me____release_on_exit  mtk::__internal_containersupport_nevercall_me____release_on_exit();

};   //  end namespace mtk


#endif
