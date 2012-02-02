/*
 */



#ifndef mtkSignalSlotsH
#define mtkSignalSlotsH

#undef emit    //   esto es una chapu necesaria para compilar con qt que en el resto no molesta

//	JLE  23/07/2008


/**
	Pendiente...

	Hacer pruebas
	Documentar
	Ejemplos
	Revisar y probar la gestión de la memoria (codeguard y valgrid)

	No permitir bucles con signal o sólo permitirlo para 100 vueltas
	¿Prioridades?
	Que se devuelva al emitir la señal el número de receptores suscritos que la han recibido

	¿Permitir y/o avisar en caso de una doble conexión?
	Es decir que un método recibirá dos llamadas por un mismo signal

	SignalReceptor tiene que ser copiable


*/


#include <list>
#include <stdexcept>    //  run_time_error exception
#include <iostream>

#include "support/basic_types.hpp"
#include "support/count_ptr.hpp"
#include "support/tuples.hpp"




#define MTK_CONNECT_THIS(CT_SIGNAL, CT_METHOD_NAME)     (CT_SIGNAL).connect(this, &CLASS_NAME::CT_METHOD_NAME);





namespace mtk {



const int SIGNAL_SLOT_MAX_DEEP_EMIT = 20;


//----------------------------------------------------------------------------

//      DECLARACIONES ANTICIPADAS

//----------------------------------------------------------------------------





template    <       typename TP0=null_type,
                    typename TP1=null_type,
                    typename TP2=null_type,
                    typename TP3=null_type,
                    typename TP4=null_type
            >
class Signal;




template    <       typename TReceiver    ,
                    typename TP0=null_type,
                    typename TP1=null_type,
                    typename TP2=null_type,
                    typename TP3=null_type,
                    typename TP4=null_type
            >
class Connection;













//----------------------------------------------------------------------------

//    B a s e C o n n e c t i o n

//----------------------------------------------------------------------------

class BaseConnection
        : private non_copyable
{
    bool disconnected;

public:
    BaseConnection() : disconnected(false) {};

    virtual ~BaseConnection(){};
    virtual bool isSame(BaseConnection*)= 0; //  multimétodo manual

    void Disconnect(void) {
        disconnected = true;
    };

    bool IsDisconnected(void) const { return disconnected; };

};









//----------------------------------------------------------------------------

//      S i g n a l R e c e p t o r

//----------------------------------------------------------------------------



class SignalReceptor : private non_copyable {    //  esta sí deberá poderse copiar
    typedef CountPtr<BaseConnection> cptrBaseConnection;


    std::list<cptrBaseConnection> listConnections;

public:
    SignalReceptor(void) {};

    void RegisterConnection(cptrBaseConnection pconnection) {
        //pconnection.DANGEROUS_ThisInstance_NOT_Delete();
        listConnections.push_back(pconnection);
        (--listConnections.end())->DANGEROUS_ThisInstance_NOT_Delete();
    };

    void UnRegisterConnection(cptrBaseConnection connection) {
        for(auto itConnection = listConnections.begin(); itConnection != listConnections.end(); ++itConnection)
        {
            //  es seguro borrar directamente desde aquí, porque sólo se itera
            //  la lista en este punto y en el destructor
            if ( (*itConnection).isValid()==false ) {
                itConnection = listConnections.erase(itConnection);
                --itConnection;
            }

            //  limpieza
            else if ( (*itConnection)->IsDisconnected()) {
                itConnection = listConnections.erase(itConnection);
                --itConnection;
            }
            else if ( (*itConnection)->isSame(connection.get2()) ) {
                (*itConnection)->Disconnect();
                itConnection = listConnections.erase(itConnection);
                --itConnection;
            }
        }
    };

    virtual ~SignalReceptor(void) {
        try{
        //  avisar a las señales que nos apuntan de que nos vamos...
            for(auto itConnection = listConnections.begin(); itConnection != listConnections.end(); ++itConnection)
            {
                if ( (*itConnection).isValid()==false ) {
                    itConnection = listConnections.erase(itConnection);
                    --itConnection;
                    continue;
                }
                (*itConnection)->Disconnect();
            }
        } catch(...){
            std::cerr << __PRETTY_FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"  << "exception on destructor"  <<  std::endl;
        }
    };

};
















//----------------------------------------------------------------------------

//      I M P L E M E N T A C I Ó N     0    P A R Á M E T R O S

//----------------------------------------------------------------------------



class BaseConnection0
        : public BaseConnection
{

public:
    BaseConnection0() : BaseConnection() {};

    virtual ~BaseConnection0(){};

    virtual void emit(void)=0;

    virtual SignalReceptor*  GetSignalReceptor(void) const  = 0;

};





template<typename TReceiver>
class Connection
            < TReceiver, null_type, null_type, null_type, null_type, null_type>
        : public BaseConnection0
{
    TReceiver* pt2Object;
    void (TReceiver::*fpt)(void);


public:
    Connection(TReceiver* _pt2Object, void (TReceiver::*_fpt)(void))
        :   pt2Object(_pt2Object),
            fpt(_fpt)
        {}

    void emit(void){
        (*pt2Object.*fpt)();
    };



    TReceiver* GetReceiver(void)  {
        return pt2Object;
    };
    void (TReceiver::*GetFuncPointer(void)) (void)   {
        return fpt;
    };

    bool isSame(BaseConnection* pbc)  //  multimétodo manual
    {
        Connection<TReceiver>* pc = dynamic_cast<Connection<TReceiver>* > (pbc);
        if (pc)
            return this == pc;  //isSameC(pc);
        else
            return false;
    }

//    bool isSameC(Connection<TReceiver>* c)  //  multimétodo manual
//    {
//        if (
//                GetReceiver()       ==  c->GetReceiver()
//                &&
//                GetFuncPointer()    ==  c->GetFuncPointer()
//            )
//                return true;
//        else
//                return false;
//    }

    SignalReceptor*  GetSignalReceptor(void) const {
        return pt2Object;
    }

};





template <>
class Signal
        <null_type, null_type, null_type, null_type, null_type>
        :   public SignalReceptor//,public non_copyable (implicit)
{
	int processing_emit;
    std::list< CountPtr<BaseConnection0 > > connections;

    //  conexión con funciones   (puntero e información de si está conectado)
    std::list< mtk::tuple<void (*)(void), bool> >  functConnections;


public:
	Signal() : processing_emit(0) {}

	~Signal() {
        try{
            disconnect_all();
            if (processing_emit>0)
                throw std::runtime_error("~Signal<> on emit");
                //	no se deben lanzar excepciones desde señales
                //	pero en este caso, es una clase que no hereda ni heredan de ella
        } catch(...){
            std::cerr << __PRETTY_FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"  << "exception on destructor"  <<  std::endl;
        }
    }

	int get_processing_emits(void) const {  return  processing_emit; }

    template<typename TReceiver>
    void connect(TReceiver* receiver, void (TReceiver::*fpt)(void)) {
        CountPtr<BaseConnection0>
                pbc (    new Connection<
                                        TReceiver,
                                        null_type,
                                        null_type,
                                        null_type,
                                        null_type,
                                        null_type
                                    >(receiver, fpt)
                    );
        connections.push_back(pbc);
        //pbc.DANGEROUS_ThisInstance_NOT_Delete();  //  lo hace el receptor
        receiver->RegisterConnection(CountPtr<BaseConnection>(pbc));
    };

    template<typename TReceiver>
    bool disconnect(TReceiver* receiver, void (TReceiver::*fpt)(void)) {
        for(auto it2ptrBaseConnection = connections.begin(); it2ptrBaseConnection != connections.end(); ++it2ptrBaseConnection)
        {
            Connection<TReceiver>* pconnection = dynamic_cast<Connection<TReceiver>* > (it2ptrBaseConnection->get2());
            if  (
                    pconnection
                    &&
                    pconnection->GetReceiver()    == receiver
                    &&
                    pconnection->GetFuncPointer() == fpt
                    &&
                    (*it2ptrBaseConnection)->IsDisconnected() == false  //  esta línea es necesaria, pero reduce mucho el rendimiento
                )
            {
                receiver->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
                //  OJO alguien podría tener la genial idea de desconectar desde
                //  el método llamado por emit
                //  revisado 29/07/2008
                    //  no es seguro eliminar desde aquí de la lista, porque también se itera
                    //  en emit y se pueden cruzar
                //connections.erase(it2ptrBaseConnection);
                //  por eso cambiamos esta línea por esta otra
                //(*it2ptrBaseConnection)->Disconnect();
                //  sino, fallará al tratar de buscar el siguient elemento
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();
				else
				{
					/*it2ptrBaseConnection = */connections.erase(it2ptrBaseConnection);
					//--it2ptrBaseConnection;		esto no es necesario porque no iteramos más
				}

                return true;
            }
        }
        return false;
    };

    void disconnect_all(void) {
        //  limpieza
        for(auto it2ptrBaseConnection = connections.begin(); it2ptrBaseConnection != connections.end(); ++it2ptrBaseConnection)
        {
            if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
                SignalReceptor* sr = (*it2ptrBaseConnection)->GetSignalReceptor();
                sr->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();

            }
        }

        //functConnections = std::list< mtk::tuple<void (*)(void), bool> >();   //  lo borramos todo
        //functConnections.clear();
		if (processing_emit>0)
		{
            for(auto itconnection2funct = functConnections.begin(); itconnection2funct != functConnections.end(); ++itconnection2funct)
            {
				itconnection2funct->_1 = false;
			}
		}
		else
		{
			functConnections.clear();
			connections.clear();
		}

    };

    int emit(void) {
        int count=0;
		try
		{
			++processing_emit;
			if (processing_emit>mtk::SIGNAL_SLOT_MAX_DEEP_EMIT)
				throw std::runtime_error("too deep recursion on emit");

            for(auto itconnection = connections.begin(); itconnection != connections.end(); ++itconnection)
            {
				if ( (*itconnection)->IsDisconnected() == false) {
					//  OJO alguien podría tener la genial idea de desconectar desde
					//  el método llamado por emit (o sucedáneos)
					(*itconnection)->emit();
					++count;
				}
				else {
					itconnection = connections.erase(itconnection);
					--itconnection;
					//  no es necesario llamar a unregister, porque al desconectar
					//  ya se ha llamado (o la desconexión es porque ha salido de
					//  ámbito SignalReceiver)
				}
			};


					//  ahora para las funciones
            for(auto itconnection2funct = functConnections.begin(); itconnection2funct != functConnections.end(); ++itconnection2funct)
			{
				if (itconnection2funct->_1)
				{
					(itconnection2funct->_0)();
					//(*(*itconnection2funct))();    //  también vale aunque es redundante
					++count;
				}
				else
				{
					itconnection2funct = functConnections.erase(itconnection2funct);
					--itconnection2funct;
				}
			}
		}
		catch (...)
		{
			--processing_emit;
			//	una de las razones podría ser la destrucción de la señal mientras estamos en el emit
			//	pero no la única
			throw;
		}
		--processing_emit;
        return count;
    };

    void operator()(void) {
        emit();
    };

    //  atajo sintáctico para conectar con otras señales
    template<typename TReceiver>
    void connect(TReceiver* receiver) {
        connect(receiver, &mtk::Signal<>::operator());
    }


    //  conexión con funciones ----------------------------------------
    void connect( void (*pt2Function)(void) ) {
        functConnections.push_back( mtk::make_tuple(pt2Function, true));
    }

    bool disconnect( void (*pt2Function)(void) ) {
        // esto no sirve, porque aquí no se deberían borrar, sólo se deberían anotar como borrados
        //  el borrado tiene que estar luego en el emit
        //  functConnections.remove(pt2Function);   esto es más corto, pero no nos indica si había algún elemento
        for(auto itconnection2funct = functConnections.begin(); itconnection2funct != functConnections.end(); ++itconnection2funct)
        {
            if (pt2Function == itconnection2funct->_0) {
				if(processing_emit>0)
					itconnection2funct->_1 = false;
				else
				{
					/*itconnection2funct = */functConnections.erase(itconnection2funct);
					//--itconnection2funct;		esto es innecesario porque no iteramos más
				}
                return true;
            }
        }
        return false;
    }


};











//----------------------------------------------------------------------------

//      I M P L E M E N T A C I Ó N     1    P A R Á M E T R O S

//----------------------------------------------------------------------------


template<typename TP1>
class BaseConnection1
        : public BaseConnection
{

public:
    BaseConnection1() : BaseConnection() {};

    virtual ~BaseConnection1(){};

    virtual void emit(TP1)=0;

    virtual SignalReceptor*  GetSignalReceptor(void) const  = 0;

};





template<typename TReceiver, typename TP1>
class Connection
            < TReceiver, TP1, null_type, null_type, null_type, null_type>
        : public BaseConnection1<TP1>
{
    TReceiver* pt2Object;
    void (TReceiver::*fpt)(TP1);


public:
    Connection(TReceiver* _pt2Object, void (TReceiver::*_fpt)(TP1))
        :   pt2Object(_pt2Object),
            fpt(_fpt)
        {}

    void emit(TP1 p1){
        (*pt2Object.*fpt)(p1);
    };



    TReceiver* GetReceiver(void)  {
        return pt2Object;
    };
    void (TReceiver::*GetFuncPointer()) (TP1)   {
        return fpt;
    };

    bool isSame(BaseConnection* pbc)  //  multimétodo manual
    {
        Connection<TReceiver, TP1>* pc = dynamic_cast<Connection<TReceiver, TP1>* > (pbc);
        if (pc)
            return this == pc;  //isSameC(pc);
        else
            return false;
    }

//    bool isSameC(Connection<TReceiver, TP1>* c)  //  multimétodo manual
//    {
//        if (
//                GetReceiver()       ==  c->GetReceiver()
//                &&
//                GetFuncPointer()    ==  c->GetFuncPointer()
//            )
//                return true;
//        else
//                return false;
//    }

    SignalReceptor*  GetSignalReceptor(void) const {
        return pt2Object;
    }

};





template <typename TP1>
class Signal
        <TP1, null_type, null_type, null_type, null_type>
        :   public SignalReceptor//,private non_copyable
{
	int processing_emit;
    std::list< CountPtr<BaseConnection1<TP1> > >    connections;

    //  conexión con funciones
    std::list< mtk::tuple<void (*)(TP1), bool> >  functConnections;


public:
	Signal() : processing_emit(0) {}

    ~Signal() {
        try{
            disconnect_all();
            if (processing_emit)
                throw std::runtime_error("~Signal<> on emit");
                //	no se deben lanzar excepciones desde señales
                //	pero en este caso, es una clase que no hereda ni heredan de ella
        } catch(...){
            std::cerr << __PRETTY_FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"  << "exception on destructor"  <<  std::endl;
        }
    }

	int get_processing_emits(void) const {  return  processing_emit; }

    template<typename TReceiver>
    void connect(TReceiver* receiver, void (TReceiver::*fpt)(TP1)) {
        CountPtr<BaseConnection1<TP1> >
                pbc (    new Connection<
                                        TReceiver,
                                        TP1		 ,
                                        null_type,
                                        null_type,
                                        null_type,
                                        null_type
                                    >(receiver, fpt)
                    );
        connections.push_back(pbc);
        receiver->RegisterConnection(CountPtr<BaseConnection>(pbc));
    };

    template<typename TReceiver>
    bool disconnect(TReceiver* receiver, void(TReceiver::*fpt)(TP1)) {
        for (
                auto  it2ptrBaseConnection = connections.begin();
                it2ptrBaseConnection != connections.end();
                ++it2ptrBaseConnection
            )
        {
            Connection<TReceiver, TP1>* pconnection = dynamic_cast<Connection<TReceiver, TP1>* > (it2ptrBaseConnection->get2());
            if  (
                    pconnection
                    &&
                    pconnection->GetReceiver()    == receiver
                    &&
                    pconnection->GetFuncPointer() == fpt
                    &&
                    (*it2ptrBaseConnection)->IsDisconnected() == false  //  esta línea es necesaria, pero reduce mucho el rendimiento
                )
            {
                //  OJO alguien podría tener la genial idea de desconectar desde
                //  el método llamado por emit
                //  revisado 29/07/2008
                    //  no es seguro eliminar desde aquí de la lista, porque también se itera
                    //  en emit y se pueden cruzar
                //connections.erase(it2ptrBaseConnection);
                //  por eso cambiamos esta línea por esta otra
                //(*it2ptrBaseConnection)->Disconnect();
                //  sino, fallará al tratar de buscar el siguient elemento

                receiver->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();
				else
				{
					/*it2ptrBaseConnection = */connections.erase(it2ptrBaseConnection);
					//--it2ptrBaseConnection;		no es necesario porque no iteramos más
				}
                return true;
            }
        }
        return false;
    };

    void disconnect_all(void) {
        //  limpieza
        for (
                auto  it2ptrBaseConnection = connections.begin();
                it2ptrBaseConnection != connections.end();
                ++it2ptrBaseConnection
            )
        {
            if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();

				SignalReceptor* sr = (*it2ptrBaseConnection)->GetSignalReceptor();
                sr->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
            }
        }

        //functConnections = std::list< mtk::tuple<void (*)(TP1), bool> >();   //  lo borramos todo
        //functConnections.clear();
		if(processing_emit>0)
		{
			typename std::list< mtk::tuple<void (*)(TP1), bool> >::iterator itconnection2funct = functConnections.begin();
			while (itconnection2funct != functConnections.end())
			{
				itconnection2funct->_1 = false;
				++itconnection2funct;
			};
		}
		else
		{
			connections.clear();
			functConnections.clear();
		}

    };

    int emit(TP1 p1) {
		int count=0;
		try
		{
			++processing_emit;
			if (processing_emit>mtk::SIGNAL_SLOT_MAX_DEEP_EMIT)
				throw std::runtime_error("too deep recursion on emit");
			for (
					auto  it2ptrBaseConnection = connections.begin();
					it2ptrBaseConnection != connections.end();
					++it2ptrBaseConnection
				)
			{
				if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
					//  OJO alguien podría tener la genial idea de desconectar desde
					//  el método llamado por emit (o sucedáneos)
					(*it2ptrBaseConnection)->emit(p1);
					++count;
				}
				else {
					it2ptrBaseConnection = connections.erase(it2ptrBaseConnection);
					--it2ptrBaseConnection;
					//  no es necesario llamar a unregister, porque al desconectar
					//  ya se ha llamado (o la desconexión es porque ha salido de
					//  ámbito SignalReceiver)
				}
			}


			//  ahora para las funciones
			typename std::list< mtk::tuple<void (*)(TP1), bool> >::iterator itconnection2funct = functConnections.begin();
			while (itconnection2funct != functConnections.end())
			{
				if (itconnection2funct->_1)
				{
					(itconnection2funct->_0)(p1);
					++itconnection2funct;
					//((*itconnection2funct))(p1);    //  también vale aunque es redundante
					++count;
				}
				else
				{
					itconnection2funct = functConnections.erase(itconnection2funct);
				}
			}
		}
		catch (...)
		{
			--processing_emit;
			//	una de las razones podría ser la destrucción de la señal mientras estamos en el emit
			//	pero no la única
			throw;
		}
		--processing_emit;
        return count;
    };
    void operator()(TP1 p1) {
        emit(p1);
    };

    template<typename TReceiver>
    void connect(TReceiver* receiver) {
        connect(receiver, &mtk::Signal<TP1>::operator());
    }


    //  conexión con funciones ----------------------------------------
    void connect( void (*pt2Function)(TP1) ) {
        functConnections.push_back(mtk::make_tuple(pt2Function, true));
    }

    bool disconnect( void (*pt2Function)(TP1) ) {
        typename std::list< mtk::tuple<void (*)(TP1), bool> >::iterator itconnection2funct = functConnections.begin();
        while (itconnection2funct != functConnections.end())
        {
            if (pt2Function == itconnection2funct->_0) {
				if(processing_emit>0)
					itconnection2funct->_1 = false;
				else
				{
					/*itconnection2funct = */functConnections.erase(itconnection2funct);
					//--itconnection2funct;		no es necesario porque no iteramos más
				}
                return true;
            }
            ++itconnection2funct;
        };
        return false;
    }

};








//----------------------------------------------------------------------------

//      I M P L E M E N T A C I Ó N     2    P A R Á M E T R O S

//----------------------------------------------------------------------------


template<typename TP1, typename TP2>
class BaseConnection2
        : public BaseConnection
{

public:
    BaseConnection2() : BaseConnection() {};

    virtual ~BaseConnection2(){};

    virtual void emit(TP1, TP2)=0;

    virtual SignalReceptor*  GetSignalReceptor(void) const  = 0;

};





template<typename TReceiver, typename TP1, typename TP2>
class Connection
            < TReceiver, TP1, TP2, null_type, null_type, null_type>
        : public BaseConnection2<TP1, TP2>
{
    TReceiver* pt2Object;
    void (TReceiver::*fpt)(TP1, TP2);


public:
    Connection(TReceiver* _pt2Object, void (TReceiver::*_fpt)(TP1, TP2))
        :   pt2Object(_pt2Object),
            fpt(_fpt)
        {}

    void emit(TP1 p1, TP2 p2){
        (*pt2Object.*fpt)(p1, p2);
    };



    TReceiver* GetReceiver(void)  {
        return pt2Object;
    };
    void (TReceiver::*GetFuncPointer()) (TP1, TP2)   {
        return fpt;
    };

    bool isSame(BaseConnection* pbc)  //  multimétodo manual
    {
        Connection<TReceiver, TP1, TP2>* pc = dynamic_cast<Connection<TReceiver, TP1, TP2>* > (pbc);
        if (pc)
            return this == pc;  //isSameC(pc);
        else
            return false;
    }

//    bool isSameC(Connection<TReceiver, TP1, TP2>* c)  //  multimétodo manual
//    {
//        if (
//                GetReceiver()       ==  c->GetReceiver()
//                &&
//                GetFuncPointer()    ==  c->GetFuncPointer()
//            )
//                return true;
//        else
//                return false;
//    }

    SignalReceptor*  GetSignalReceptor(void) const {
        return pt2Object;
    }

};





template <typename TP1, typename TP2>
class Signal
        <TP1, TP2, null_type, null_type, null_type>
        :   public SignalReceptor//,private non_copyable
{
	int processing_emit;
    std::list< CountPtr<BaseConnection2<TP1, TP2> > > connections;

    //  conexión con funciones
    std::list< mtk::tuple<void (*)(TP1, TP2), bool> >  functConnections;


public:
	Signal() : processing_emit(0) {}

    ~Signal() {
        try{
            disconnect_all();
            if (processing_emit)
                throw std::runtime_error("~Signal<> on emit");
                //	no se deben lanzar excepciones desde señales
                //	pero en este caso, es una clase que no hereda ni heredan de ella
        } catch(...){
            std::cerr << __PRETTY_FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"  << "exception on destructor"  <<  std::endl;
        }
    }

	int get_processing_emits(void) const {  return  processing_emit; }

    template<typename TReceiver>
    void connect(TReceiver* receiver, void (TReceiver::*fpt)(TP1, TP2)) {
        CountPtr<BaseConnection2<TP1, TP2> >
                pbc (    new Connection<
                                        TReceiver,
                                        TP1		 ,
                                        TP2		 ,
                                        null_type,
                                        null_type,
                                        null_type
                                    >(receiver, fpt)
                    );
        connections.push_back(pbc);
        receiver->RegisterConnection(CountPtr<BaseConnection>(pbc));
    };

    template<typename TReceiver>
    bool disconnect(TReceiver* receiver, void(TReceiver::*fpt)(TP1, TP2)) {
        for (
                auto  it2ptrBaseConnection = connections.begin();
                it2ptrBaseConnection != connections.end();
                ++it2ptrBaseConnection
            )
        {
            Connection<TReceiver, TP1, TP2>* pconnection = dynamic_cast<Connection<TReceiver, TP1, TP2>* > (it2ptrBaseConnection->get2());
            if  (
                    pconnection
                    &&
                    pconnection->GetReceiver()    == receiver
                    &&
                    pconnection->GetFuncPointer() == fpt
                    &&
                    (*it2ptrBaseConnection)->IsDisconnected() == false  //  esta línea es necesaria, pero reduce mucho el rendimiento
                )
            {
                //  OJO alguien podría tener la genial idea de desconectar desde
                //  el método llamado por emit
                //  revisado 29/07/2008
                    //  no es seguro eliminar desde aquí de la lista, porque también se itera
                    //  en emit y se pueden cruzar
                //connections.erase(it2ptrBaseConnection);
                //  por eso cambiamos esta línea por esta otra
                //(*it2ptrBaseConnection)->Disconnect();
                //  sino, fallará al tratar de buscar el siguient elemento

                receiver->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();
				else
				{
					/*it2ptrBaseConnection = */connections.erase(it2ptrBaseConnection);
					//--it2ptrBaseConnection;		no es necesario porque no iteramos más
				}
                return true;
            }
        }
        return false;
    };

    void disconnect_all(void) {
        //  limpieza
        for (
                auto  it2ptrBaseConnection = connections.begin();
                it2ptrBaseConnection != connections.end();
                ++it2ptrBaseConnection
            )
        {
            if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();

				SignalReceptor* sr = (*it2ptrBaseConnection)->GetSignalReceptor();
                sr->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
            }
        }

        //functConnections = std::list< mtk::tuple<void (*)(TP1), bool> >();   //  lo borramos todo
        //functConnections.clear();
		if(processing_emit>0)
		{
			typename std::list< mtk::tuple<void (*)(TP1, TP2), bool> >::iterator itconnection2funct = functConnections.begin();
			while (itconnection2funct != functConnections.end())
			{
				itconnection2funct->_1 = false;
				++itconnection2funct;
			};
		}
		else
		{
			connections.clear();
			functConnections.clear();
		}

    };

    int emit(TP1 p1, TP2 p2) {
		int count=0;
		try
		{
			++processing_emit;
			if (processing_emit>mtk::SIGNAL_SLOT_MAX_DEEP_EMIT)
				throw std::runtime_error("too deep recursion on emit");
			for (
					auto  it2ptrBaseConnection = connections.begin();
					it2ptrBaseConnection != connections.end();
					++it2ptrBaseConnection
				)
			{
				if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
					//  OJO alguien podría tener la genial idea de desconectar desde
					//  el método llamado por emit (o sucedáneos)
					(*it2ptrBaseConnection)->emit(p1, p2);
					++count;
				}
				else {
					it2ptrBaseConnection = connections.erase(it2ptrBaseConnection);
					--it2ptrBaseConnection;
					//  no es necesario llamar a unregister, porque al desconectar
					//  ya se ha llamado (o la desconexión es porque ha salido de
					//  ámbito SignalReceiver)
				}
			}


			//  ahora para las funciones
			typename std::list< mtk::tuple<void (*)(TP1, TP2), bool> >::iterator itconnection2funct = functConnections.begin();
			while (itconnection2funct != functConnections.end())
			{
				if (itconnection2funct->_1)
				{
					(itconnection2funct->_0)(p1, p2);
					++itconnection2funct;
					//((*itconnection2funct))(p1);    //  también vale aunque es redundante
					++count;
				}
				else
				{
					itconnection2funct = functConnections.erase(itconnection2funct);
				}
			}
		}
		catch (...)
		{
			--processing_emit;
			//	una de las razones podría ser la destrucción de la señal mientras estamos en el emit
			//	pero no la única
			throw;
		}
		--processing_emit;
        return count;
    };
    void operator()(TP1 p1, TP2 p2) {
        emit(p1, p2);
    };

    template<typename TReceiver>
    void connect(TReceiver* receiver) {
        connect(receiver, &mtk::Signal<TP1, TP2>::operator());
    }


    //  conexión con funciones ----------------------------------------
    void connect( void (*pt2Function)(TP1, TP2) ) {
        functConnections.push_back(mtk::make_tuple(pt2Function, true));
    }

    bool disconnect( void (*pt2Function)(TP1, TP2) ) {
        typename std::list< mtk::tuple<void (*)(TP1, TP2), bool> >::iterator itconnection2funct = functConnections.begin();
        while (itconnection2funct != functConnections.end())
        {
            if (pt2Function == itconnection2funct->_0) {
				if(processing_emit>0)
					itconnection2funct->_1 = false;
				else
				{
					/*itconnection2funct = */functConnections.erase(itconnection2funct);
					//--itconnection2funct;		no es necesario porque no iteramos más
				}
                return true;
            }
            ++itconnection2funct;
        };
        return false;
    }

};







//----------------------------------------------------------------------------

//      I M P L E M E N T A C I Ó N     3    P A R Á M E T R O S

//----------------------------------------------------------------------------


template<typename TP1, typename TP2, typename TP3>
class BaseConnection3
        : public BaseConnection
{

public:
    BaseConnection3() : BaseConnection() {};

    virtual ~BaseConnection3(){};

    virtual void emit(TP1, TP2, TP3)=0;

    virtual SignalReceptor*  GetSignalReceptor(void) const  = 0;

};





template<typename TReceiver, typename TP1, typename TP2, typename TP3>
class Connection
            < TReceiver, TP1, TP2, TP3, null_type, null_type>
        : public BaseConnection3<TP1, TP2, TP3>
{
    TReceiver* pt2Object;
    void (TReceiver::*fpt)(TP1, TP2, TP3);


public:
    Connection(TReceiver* _pt2Object, void (TReceiver::*_fpt)(TP1, TP2, TP3))
        :   pt2Object(_pt2Object),
            fpt(_fpt)
        {}

    void emit(TP1 p1, TP2 p2, TP3 p3){
        (*pt2Object.*fpt)(p1, p2, p3);
    };



    TReceiver* GetReceiver(void)  {
        return pt2Object;
    };
    void (TReceiver::*GetFuncPointer()) (TP1, TP2, TP3)   {
        return fpt;
    };

    bool isSame(BaseConnection* pbc)  //  multimétodo manual
    {
        Connection<TReceiver, TP1, TP2, TP3>* pc = dynamic_cast<Connection<TReceiver, TP1, TP2, TP3>* > (pbc);
        if (pc)
            return this == pc;  //isSameC(pc);
        else
            return false;
    }

//    bool isSameC(Connection<TReceiver, TP1, TP2, TP3>* c)  //  multimétodo manual
//    {
//        if (
//                GetReceiver()       ==  c->GetReceiver()
//                &&
//                GetFuncPointer()    ==  c->GetFuncPointer()
//            )
//                return true;
//        else
//                return false;
//    }

    SignalReceptor*  GetSignalReceptor(void) const {
        return pt2Object;
    }

};





template <typename TP1, typename TP2, typename TP3>
class Signal
        <TP1, TP2, TP3, null_type, null_type>
        :   public SignalReceptor//,private non_copyable
{
	int processing_emit;
    std::list< CountPtr<BaseConnection3<TP1, TP2, TP3> > >   connections;

    //  conexión con funciones
    std::list< mtk::tuple<void (*)(TP1, TP2, TP3), bool> >  functConnections;


public:
	Signal() : processing_emit(0) {}

    ~Signal() {
        try{
            disconnect_all();
            if (processing_emit)
                throw std::runtime_error("~Signal<> on emit");
                //	no se deben lanzar excepciones desde señales
                //	pero en este caso, es una clase que no hereda ni heredan de ella
        } catch(...){
            std::cerr << __PRETTY_FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"  << "exception on destructor"  <<  std::endl;
        }
    }

	int get_processing_emits(void) const {  return  processing_emit; }

    template<typename TReceiver>
    void connect(TReceiver* receiver, void (TReceiver::*fpt)(TP1, TP2, TP3)) {
        CountPtr<BaseConnection3<TP1, TP2, TP3> >
                pbc (    new Connection<
                                        TReceiver,
                                        TP1		 ,
                                        TP2		 ,
                                        TP3		 ,
                                        null_type,
                                        null_type
                                    >(receiver, fpt)
                    );
        connections.push_back(pbc);
        receiver->RegisterConnection(CountPtr<BaseConnection>(pbc));
    };

    template<typename TReceiver>
    bool disconnect(TReceiver* receiver, void(TReceiver::*fpt)(TP1, TP2, TP3)) {
        for (
                auto  it2ptrBaseConnection = connections.begin();
                it2ptrBaseConnection != connections.end();
                ++it2ptrBaseConnection
            )
        {
            Connection<TReceiver, TP1, TP2, TP3>* pconnection = dynamic_cast<Connection<TReceiver, TP1, TP2, TP3>* > (it2ptrBaseConnection->get2());
            if  (
                    pconnection
                    &&
                    pconnection->GetReceiver()    == receiver
                    &&
                    pconnection->GetFuncPointer() == fpt
                    &&
                    (*it2ptrBaseConnection)->IsDisconnected() == false  //  esta línea es necesaria, pero reduce mucho el rendimiento
                )
            {
                //  OJO alguien podría tener la genial idea de desconectar desde
                //  el método llamado por emit
                //  revisado 29/07/2008
                    //  no es seguro eliminar desde aquí de la lista, porque también se itera
                    //  en emit y se pueden cruzar
                //connections.erase(it2ptrBaseConnection);
                //  por eso cambiamos esta línea por esta otra
                //(*it2ptrBaseConnection)->Disconnect();
                //  sino, fallará al tratar de buscar el siguient elemento

                receiver->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();
				else
				{
					/*it2ptrBaseConnection = */connections.erase(it2ptrBaseConnection);
					//--it2ptrBaseConnection;		no es necesario porque no iteramos más
				}
                return true;
            }
        }
        return false;
    };

    void disconnect_all(void) {
        //  limpieza
        for (
                auto  it2ptrBaseConnection = connections.begin();
                it2ptrBaseConnection != connections.end();
                ++it2ptrBaseConnection
            )
        {
            if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();

				SignalReceptor* sr = (*it2ptrBaseConnection)->GetSignalReceptor();
                sr->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
            }
        }

        //functConnections = std::list< mtk::tuple<void (*)(TP1), bool> >();   //  lo borramos todo
        //functConnections.clear();
		if(processing_emit>0)
		{
			typename std::list< mtk::tuple<void (*)(TP1, TP2, TP3), bool> >::iterator itconnection2funct = functConnections.begin();
			while (itconnection2funct != functConnections.end())
			{
				itconnection2funct->_1 = false;
				++itconnection2funct;
			};
		}
		else
		{
			connections.clear();
			functConnections.clear();
		}

    };

    int emit(TP1 p1, TP2 p2, TP3 p3) {
		int count=0;
		try
		{
			++processing_emit;
			if (processing_emit>mtk::SIGNAL_SLOT_MAX_DEEP_EMIT)
				throw std::runtime_error("too deep recursion on emit");
			for (
					auto  it2ptrBaseConnection = connections.begin();
					it2ptrBaseConnection != connections.end();
					++it2ptrBaseConnection
				)
			{
				if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
					//  OJO alguien podría tener la genial idea de desconectar desde
					//  el método llamado por emit (o sucedáneos)
					(*it2ptrBaseConnection)->emit(p1, p2, p3);
					++count;
				}
				else {
					it2ptrBaseConnection = connections.erase(it2ptrBaseConnection);
					--it2ptrBaseConnection;
					//  no es necesario llamar a unregister, porque al desconectar
					//  ya se ha llamado (o la desconexión es porque ha salido de
					//  ámbito SignalReceiver)
				}
			}


			//  ahora para las funciones
			typename std::list< mtk::tuple<void (*)(TP1, TP2, TP3), bool> >::iterator itconnection2funct = functConnections.begin();
			while (itconnection2funct != functConnections.end())
			{
				if (itconnection2funct->_1)
				{
					(itconnection2funct->_0)(p1, p2, p3);
					++itconnection2funct;
					//((*itconnection2funct))(p1);    //  también vale aunque es redundante
					++count;
				}
				else
				{
					itconnection2funct = functConnections.erase(itconnection2funct);
				}
			}
		}
		catch (...)
		{
			--processing_emit;
			//	una de las razones podría ser la destrucción de la señal mientras estamos en el emit
			//	pero no la única
			throw;
		}
		--processing_emit;
        return count;
    };
    void operator()(TP1 p1, TP2 p2, TP3 p3) {
        emit(p1, p2, p3);
    };

    template<typename TReceiver>
    void connect(TReceiver* receiver) {
        connect(receiver, &mtk::Signal<TP1, TP2, TP3>::operator());
    }


    //  conexión con funciones ----------------------------------------
    void connect( void (*pt2Function)(TP1, TP2, TP3) ) {
        functConnections.push_back(mtk::make_tuple(pt2Function, true));
    }

    bool disconnect( void (*pt2Function)(TP1, TP2, TP3) ) {
        typename std::list< mtk::tuple<void (*)(TP1, TP2, TP3), bool> >::iterator itconnection2funct = functConnections.begin();
        while (itconnection2funct != functConnections.end())
        {
            if (pt2Function == itconnection2funct->_0) {
				if(processing_emit>0)
					itconnection2funct->_1 = false;
				else
				{
					/*itconnection2funct = */functConnections.erase(itconnection2funct);
					//--itconnection2funct;		no es necesario porque no iteramos más
				}
                return true;
            }
            ++itconnection2funct;
        };
        return false;
    }

};








//----------------------------------------------------------------------------

//      I M P L E M E N T A C I Ó N     4    P A R Á M E T R O S

//----------------------------------------------------------------------------


template<typename TP1, typename TP2, typename TP3, typename TP4>
class BaseConnection4
        : public BaseConnection
{

public:
    BaseConnection4() : BaseConnection() {};

    virtual ~BaseConnection4(){};

    virtual void emit(TP1, TP2, TP3, TP4)=0;

    virtual SignalReceptor*  GetSignalReceptor(void) const  = 0;

};





template<typename TReceiver, typename TP1, typename TP2, typename TP3, typename TP4>
class Connection
            < TReceiver, TP1, TP2, TP3, TP4, null_type>
        : public BaseConnection4<TP1, TP2, TP3, TP4>
{
    TReceiver* pt2Object;
    void (TReceiver::*fpt)(TP1, TP2, TP3, TP4);


public:
    Connection(TReceiver* _pt2Object, void (TReceiver::*_fpt)(TP1, TP2, TP3, TP4))
        :   pt2Object(_pt2Object),
            fpt(_fpt)
        {}

    void emit(TP1 p1, TP2 p2, TP3 p3, TP4 p4){
        (*pt2Object.*fpt)(p1, p2, p3, p4);
    };



    TReceiver* GetReceiver(void)  {
        return pt2Object;
    };
    void (TReceiver::*GetFuncPointer()) (TP1, TP2, TP3, TP4)   {
        return fpt;
    };

    bool isSame(BaseConnection* pbc)  //  multimétodo manual
    {
        Connection<TReceiver, TP1, TP2, TP3, TP4>* pc = dynamic_cast<Connection<TReceiver, TP1, TP2, TP3, TP4>* > (pbc);
        if (pc)
            return this == pc;  //isSameC(pc);
        else
            return false;
    }

//    bool isSameC(Connection<TReceiver, TP1, TP2, TP3, TP4>* c)  //  multimétodo manual
//    {
//        if (
//                GetReceiver()       ==  c->GetReceiver()
//                &&
//                GetFuncPointer()    ==  c->GetFuncPointer()
//            )
//                return true;
//        else
//                return false;
//    }

    SignalReceptor*  GetSignalReceptor(void) const {
        return pt2Object;
    }

};





template <typename TP1, typename TP2, typename TP3, typename TP4>
class Signal
        <TP1, TP2, TP3, TP4, null_type>
        :   public SignalReceptor//,private non_copyable
{
	int processing_emit;
    std::list< CountPtr<BaseConnection4<TP1, TP2, TP3, TP4> > >   connections;

    //  conexión con funciones
    std::list< mtk::tuple<void (*)(TP1, TP2, TP3, TP4), bool> >  functConnections;


public:
	Signal() : processing_emit(0) {}

    ~Signal() {
        try{
            disconnect_all();
            if (processing_emit)
                throw std::runtime_error("~Signal<> on emit");
                //	no se deben lanzar excepciones desde señales
                //	pero en este caso, es una clase que no hereda ni heredan de ella
        } catch(...){
            std::cerr << __PRETTY_FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")"  << "exception on destructor"  <<  std::endl;
        }
    }

	int get_processing_emits(void) const {  return  processing_emit; }

    template<typename TReceiver>
    void connect(TReceiver* receiver, void (TReceiver::*fpt)(TP1, TP2, TP3, TP4)) {
        CountPtr<BaseConnection4<TP1, TP2, TP3, TP4> >
                pbc (    new Connection<
                                        TReceiver,
                                        TP1		 ,
                                        TP2		 ,
                                        TP3		 ,
                                        TP4		 ,
                                        null_type
                                    >(receiver, fpt)
                    );
        connections.push_back(pbc);
        receiver->RegisterConnection(CountPtr<BaseConnection>(pbc));
    };

    template<typename TReceiver>
    bool disconnect(TReceiver* receiver, void(TReceiver::*fpt)(TP1, TP2, TP3, TP4)) {
        for (
                auto  it2ptrBaseConnection = connections.begin();
                it2ptrBaseConnection != connections.end();
                ++it2ptrBaseConnection
            )
        {
            Connection<TReceiver, TP1, TP2, TP3, TP4>* pconnection = dynamic_cast<Connection<TReceiver, TP1, TP2, TP3, TP4>* > (it2ptrBaseConnection->get2());
            if  (
                    pconnection
                    &&
                    pconnection->GetReceiver()    == receiver
                    &&
                    pconnection->GetFuncPointer() == fpt
                    &&
                    (*it2ptrBaseConnection)->IsDisconnected() == false  //  esta línea es necesaria, pero reduce mucho el rendimiento
                )
            {
                //  OJO alguien podría tener la genial idea de desconectar desde
                //  el método llamado por emit
                //  revisado 29/07/2008
                    //  no es seguro eliminar desde aquí de la lista, porque también se itera
                    //  en emit y se pueden cruzar
                //connections.erase(it2ptrBaseConnection);
                //  por eso cambiamos esta línea por esta otra
                //(*it2ptrBaseConnection)->Disconnect();
                //  sino, fallará al tratar de buscar el siguient elemento

                receiver->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();
				else
				{
					/*it2ptrBaseConnection = */connections.erase(it2ptrBaseConnection);
					//--it2ptrBaseConnection;		no es necesario porque no iteramos más
				}
                return true;
            }
        }
        return false;
    };

    void disconnect_all(void) {
        //  limpieza
        for (
                auto  it2ptrBaseConnection = connections.begin();
                it2ptrBaseConnection != connections.end();
                ++it2ptrBaseConnection
            )
        {
            if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
				if (processing_emit>0)
					(*it2ptrBaseConnection)->Disconnect();

				SignalReceptor* sr = (*it2ptrBaseConnection)->GetSignalReceptor();
                sr->UnRegisterConnection(
                                CountPtr<BaseConnection>(*it2ptrBaseConnection)
                            );
            }
        }

        //functConnections = std::list< mtk::tuple<void (*)(TP1), bool> >();   //  lo borramos todo
        //functConnections.clear();
		if(processing_emit>0)
		{
			typename std::list< mtk::tuple<void (*)(TP1, TP2, TP3, TP4), bool> >::iterator itconnection2funct = functConnections.begin();
			while (itconnection2funct != functConnections.end())
			{
				itconnection2funct->_1 = false;
				++itconnection2funct;
			};
		}
		else
		{
			connections.clear();
			functConnections.clear();
		}

    };

    int emit(TP1 p1, TP2 p2, TP3 p3, TP4 p4) {
		int count=0;
		try
		{
			++processing_emit;
			if (processing_emit>mtk::SIGNAL_SLOT_MAX_DEEP_EMIT)
				throw std::runtime_error("too deep recursion on emit");
			for (
					auto  it2ptrBaseConnection = connections.begin();
					it2ptrBaseConnection != connections.end();
					++it2ptrBaseConnection
				)
			{
				if ( (*it2ptrBaseConnection)->IsDisconnected() == false) {
					//  OJO alguien podría tener la genial idea de desconectar desde
					//  el método llamado por emit (o sucedáneos)
					(*it2ptrBaseConnection)->emit(p1, p2, p3, p4);
					++count;
				}
				else {
					it2ptrBaseConnection = connections.erase(it2ptrBaseConnection);
					--it2ptrBaseConnection;
					//  no es necesario llamar a unregister, porque al desconectar
					//  ya se ha llamado (o la desconexión es porque ha salido de
					//  ámbito SignalReceiver)
				}
			}


			//  ahora para las funciones
			typename std::list< mtk::tuple<void (*)(TP1, TP2, TP3, TP4), bool> >::iterator itconnection2funct = functConnections.begin();
			while (itconnection2funct != functConnections.end())
			{
				if (itconnection2funct->_1)
				{
					(itconnection2funct->_0)(p1, p2, p3, p4);
					++itconnection2funct;
					//((*itconnection2funct))(p1);    //  también vale aunque es redundante
					++count;
				}
				else
				{
					itconnection2funct = functConnections.erase(itconnection2funct);
				}
			}
		}
		catch (...)
		{
			--processing_emit;
			//	una de las razones podría ser la destrucción de la señal mientras estamos en el emit
			//	pero no la única
			throw;
		}
		--processing_emit;
        return count;
    };
    void operator()(TP1 p1, TP2 p2, TP3 p3, TP4 p4) {
        emit(p1, p2, p3, p4);
    };

    template<typename TReceiver>
    void connect(TReceiver* receiver) {
        connect(receiver, &mtk::Signal<TP1, TP2, TP3, TP4>::operator());
    }


    //  conexión con funciones ----------------------------------------
    void connect( void (*pt2Function)(TP1, TP2, TP3, TP4) ) {
        functConnections.push_back(mtk::make_tuple(pt2Function, true));
    }

    bool disconnect( void (*pt2Function)(TP1, TP2, TP3, TP4) ) {
        typename std::list< mtk::tuple<void (*)(TP1, TP2, TP3, TP4), bool> >::iterator itconnection2funct = functConnections.begin();
        while (itconnection2funct != functConnections.end())
        {
            if (pt2Function == itconnection2funct->_0) {
				if(processing_emit>0)
					itconnection2funct->_1 = false;
				else
				{
					/*itconnection2funct = */functConnections.erase(itconnection2funct);
					//--itconnection2funct;		no es necesario porque no iteramos más
				}
                return true;
            }
            ++itconnection2funct;
        };
        return false;
    }

};













};  //  end namespace mtk {


#endif

