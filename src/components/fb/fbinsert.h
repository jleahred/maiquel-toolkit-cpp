#ifndef  MTK_fbInsert_H
#define  MTK_fbInsert_H



/*
 * Si la cola tiene demaiados elementos, tirar la mitad y mandar un critic (situación extrema)
 *
 */



#include <string>


#include "fb/ibpp.h"
#include "support/list.hpp"
#include "support/signalslot.hpp"





namespace mtk {


class __internal_fbInsertData
{
private:
    friend class fbInsertParams;
    friend class fbInsert;

    enum enFbIDType {  __fbidtNull, __fbidtBool, __fbidtString, __fbidtInt, __fbidtDouble, __fbidtDateTime, __fbidtTimeQuantity };

    __internal_fbInsertData(void)                              : dataType(__fbidtNull)           , bValue (false),  sValue (""),    iValue (0),     dValue (0.),    dtValue(),      tqValue()       {};
    __internal_fbInsertData(bool _value)                       : dataType(__fbidtBool)           , bValue (_value), sValue (""),    iValue (0),     dValue (0.),    dtValue(),      tqValue()       {};
    __internal_fbInsertData(const std::string& _value)         : dataType(__fbidtString)         , bValue (false),  sValue (_value),iValue (0),     dValue (0.),    dtValue(),      tqValue()       {};
    __internal_fbInsertData(int _value)                        : dataType(__fbidtInt)            , bValue (false),  sValue (""),    iValue (_value),dValue (0.),    dtValue(),      tqValue()       {};
    __internal_fbInsertData(double _value)                     : dataType(__fbidtDouble)         , bValue (false),  sValue (""),    iValue (0),     dValue (_value),dtValue(),      tqValue()       {};
    __internal_fbInsertData(const mtk::dtDateTime& _value)     : dataType(__fbidtDateTime)       , bValue (false),  sValue (""),    iValue (0),     dValue (0.),    dtValue(_value),tqValue()       {};
    __internal_fbInsertData(const mtk::dtTimeQuantity& _value) : dataType(__fbidtTimeQuantity)   , bValue (false),  sValue (""),    iValue (0),     dValue (0.),    dtValue(),      tqValue(_value) {};

    enFbIDType                          dataType;
    bool                                bValue;
    std::string                         sValue;
    int                                 iValue;
    double                              dValue;
    mtk::nullable<mtk::dtDateTime>      dtValue;
    mtk::nullable<mtk::dtTimeQuantity>  tqValue;
};




class fbInsertParams
{
    friend class fbInsert;
public:
    //  sirve el constructor de copia y el operación de asignación automáticos


    void AddNull(void                             ) { lParams.push_back(__internal_fbInsertData()); }

    void Add (bool                          _value) { lParams.push_back(_value); }
    void Add (int                           _value) { lParams.push_back(_value); }
    void Add (double                        _value) { lParams.push_back(_value); }
    void Add (const mtk::dtDateTime&        _value) { lParams.push_back(_value); }
    void Add (const mtk::dtTimeQuantity&    _value) { lParams.push_back(_value); }
    void Add (const std::string&			_value) { lParams.push_back(_value); }
    void Add (const char*    				_value) { lParams.push_back(std::string(_value)); }

private:
    mtk::list<__internal_fbInsertData>    lParams;
};





//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------


class fbInsert  :  public mtk::SignalReceptor
{
    mtk::non_copyable nc;

public:

	fbInsert(const std::string& _fbi_config, const std::string& _prepare);
	~fbInsert(void);

    void Insert(const fbInsertParams& params);

    int  GetQueueSize(void)    {   return queue.size();  }

    /// número de registros a guardar por cada intento
    int                     numberOfRecords2Save;

    /// frecuencia con la que se tratarán de guardar los registros
    mtk::dtTimeQuantity     frecuency;

    ///  avisamos en warning si supera...
    int                     warningOnQueueSize;

    ///  avisamos en error si supera
    int                     errorOnQueueSize;

    /// tiempo máximo que puede estar guardando los registros
    mtk::dtTimeQuantity     maxTime2saveRecods;



private:
    IBPP::Database              db;
    std::string                 prepare;
    mtk::list<fbInsertParams>   queue;
    int                         savedRecords;
    int                         receivedRecords;
	bool						dbConnectionErrorSent;
    mtk::dtTimeQuantity         reconnect_time;
    std::string                 fbi_config;

    IBPP::Transaction TryStartTransaction(void);
    void OnTimer(void);

    void command_config (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_stats (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_status (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_set_frecuency(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_set_error_on_queue_size(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines);
    void command_set_warning_queue_size(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines);
    void command_set_max_time2save_records(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines);
    void command_set_number_of_records2save(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines);

};


};  // namespace idt {

#endif
