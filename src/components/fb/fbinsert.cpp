#include "fbinsert.h"

#include "components/admin/admin.h"
#include "fbcompsupport.h"



namespace mtk {



//--------------------------------------------------------------------------------------------


namespace
{

    const char*   VER           = "2011-04-05";
    const char*   MODIFICATIONS = "           2011-04-05     first version\n";
    
    
    
    void command_version(const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(MTK_SS(__FILE__ << ":  " << VER));
    }

    void command_modifications  (const std::string& /*command*/, const std::string& /*param*/,  mtk::list<std::string>&  response_lines)
    {
        response_lines.push_back(__FILE__);
        response_lines.push_back(".......................................");
        response_lines.push_back(MODIFICATIONS);
    }


    
    void register_global_commands (void)
    {
        mtk::admin::register_command("__GLOBAL__",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("__GLOBAL__",  "modifs",   "")->connect(command_modifications);
        mtk::admin::register_command("fbinsert",  "ver",   "")->connect(command_version);
        mtk::admin::register_command("fbinsert",  "modifs",   "")->connect(command_modifications);
    }
    
    MTK_ADMIN_REGISTER_GLOBAL_COMMANDS(register_global_commands)    
}










namespace
{


//  limit control for params
const int                   MIN_NUMBER_OF_RECORDS2SAVE      = 2;      
const int                   MAX_NUMBER_OF_RECORDS2SAVE      = 1000;

const mtk::dtTimeQuantity   MIN_FRECUENCY2SAVE              = mtk::dtMilliseconds(500);       
const mtk::dtTimeQuantity   MAX_FRECUENCY2SAVE              = mtk::dtMinutes(20);

const int                   MIN_WARNING_ON_QUEUE_SIZE       = 200;        
const int                   MAX_WARNING_ON_QUEUE_SIZE       = 10000;

const int                   MIN_ERROR_ON_QUEUE_SIZE         = 700;       
const int                   MAX_ERROR_ON_QUEUE_SIZE         = 8000;

const mtk::dtTimeQuantity   MIN_MAXTIME2SAVE_RECORDS        = mtk::dtMilliseconds(500);       
const mtk::dtTimeQuantity   MAX_MAXTIME2SAVE_RECORDS        = mtk::dtSeconds(20);





//----------------------------------------------------------------------------------------------------------------

mtk::dtTimeQuantity s_fbFrecuencyFromConfig (const std::string& configPath)
{
    mtk::dtTimeQuantity result = mtk::dtSeconds(0);
    std::string path = configPath;
    mtk::Nullable<std::string> frecuencyFBI = mtk::admin::get_config_property(MTK_SS(path << ".frecuency"));
    bool converted=false;
    if (frecuencyFBI.HasValue())
    {
        mtk::s_TRY_stotq(frecuencyFBI.Get(), result).assign(result, converted);
        if (converted == false)
            throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("frecuency converting to timequantity error " << frecuencyFBI.Get()), mtk::alPriorError);
    }
    else
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("frecuency mising  "  << configPath), mtk::alPriorError);

    if (result < MIN_FRECUENCY2SAVE)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("frecuency too low value  " << result), mtk::alPriorError);
    if (result > MAX_FRECUENCY2SAVE)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("frecuency too hight value  " << result), mtk::alPriorError);
    return result;
}

//----------------------------------------------------------------------------------------------------------------

int s_fbWarningOnQueueSizeFromConfig (const std::string& configPath)
{
    int result = 0;
    std::string path = configPath;
    mtk::Nullable<std::string> warningOnQueueSizeFBI = mtk::admin::get_config_property(MTK_SS(path << ".warningonqueuesize"));
    bool converted=false;
    if (warningOnQueueSizeFBI.HasValue())
    {
        mtk::s_TRY_stoi(warningOnQueueSizeFBI.Get(), result).assign(result, converted);
        if (converted == false)
            throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("warningOnQueueSize converting to integer error " << warningOnQueueSizeFBI.Get()), mtk::alPriorError);
    }
    else
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("warningOnQueueSize mising  " << configPath), mtk::alPriorError);

    if (result < MIN_WARNING_ON_QUEUE_SIZE)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("warningOnQueueSize too low value  " << result), mtk::alPriorError);
    if (result > MAX_WARNING_ON_QUEUE_SIZE)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("warningOnQueueSize too hight value  " << result), mtk::alPriorError);
    return result;

}


//----------------------------------------------------------------------------------------------------------------

int s_fbErrorOnQueueSizeFromConfig (const std::string& configPath)
{
    int result = 0;
    std::string path = configPath;
    mtk::Nullable<std::string> errorOnQueueSizeFBI = mtk::admin::get_config_property(MTK_SS(path << ".erroronqueuesize"));
    bool converted=false;
    if (errorOnQueueSizeFBI.HasValue())
    {
        mtk::s_TRY_stoi(errorOnQueueSizeFBI.Get(), result).assign(result, converted);
        if (converted == false)
            throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("errorOnQueueSize converting to integer error " << errorOnQueueSizeFBI.Get()), mtk::alPriorError);
    }
    else
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("errorOnQueueSize mising  " << configPath), mtk::alPriorError);

    if (result < MIN_ERROR_ON_QUEUE_SIZE)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("errorOnQueueSize too low value  " << result), mtk::alPriorError);
    if (result > MAX_ERROR_ON_QUEUE_SIZE)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("errorOnQueueSize too hight value  " << result), mtk::alPriorError);
    return result;
}


//----------------------------------------------------------------------------------------------------------------


int s_fbNumberOfRecords2SaveFromConfig (const std::string& configPath)
{
    int result = 0;
    std::string path = configPath;
    mtk::Nullable<std::string> numberOfRecords2Save = mtk::admin::get_config_property(MTK_SS(path << ".numberofrecords2save"));
    bool converted=false;
    if (numberOfRecords2Save.HasValue())
    {
        mtk::s_TRY_stoi(numberOfRecords2Save.Get(), result).assign(result, converted);
        if (converted == false)
            throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("numberOfRecords2Save converting to integer error " << numberOfRecords2Save.Get()), mtk::alPriorError);
    }
    else
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("numberOfRecords2Save mising  " << configPath), mtk::alPriorError);

    if (result < MIN_NUMBER_OF_RECORDS2SAVE)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("numberOfRecords2Save too low value  " << result), mtk::alPriorError);
    if (result > MAX_NUMBER_OF_RECORDS2SAVE)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("numberOfRecords2Save too hight value  " << result), mtk::alPriorError);
    return result;
}

//----------------------------------------------------------------------------------------------------------------

mtk::dtTimeQuantity s_fbMaxTime2saveRecodsFromConfig (const std::string& configPath)
{
    mtk::dtTimeQuantity result = mtk::dtSeconds(0);
    std::string path = configPath;
    mtk::Nullable<std::string> maxTime2SaveRecords = mtk::admin::get_config_property(MTK_SS(path << ".maxtime2saverecords"));
    bool converted=false;
    if (maxTime2SaveRecords.HasValue())
    {
        mtk::s_TRY_stotq(maxTime2SaveRecords.Get(), result).assign(result, converted);
        if (converted == false)
            throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("maxTime2SaveRecords converting to timequantity error " << maxTime2SaveRecords.Get()), mtk::alPriorError);
    }
    else
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("maxTime2SaveRecords mising  " << configPath), mtk::alPriorError);

    if (result < MIN_MAXTIME2SAVE_RECORDS)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("maxTime2SaveRecords too low value  " << result), mtk::alPriorError);
    if (result > MAX_MAXTIME2SAVE_RECORDS)
        throw mtk::Alarm(MTK_HERE, "fbinsert.readconfig", MTK_SS("maxTime2SaveRecords too hight value  " << result), mtk::alPriorError);
    return result;
}


//----------------------------------------------------------------------------------------------------------------


};  // anonymouse namespace







//----------------------------------------------------------------------------------------------------------------
void fbInsert::command_config (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("fbi." << mtk::s_toLower(fbi_config) <<"  ----------------------"));
    response_lines.push_back(MTK_SS(s_AlignLeft("prepare:"			  , 20)   << "  "  << prepare) );
    response_lines.push_back(MTK_SS(s_AlignLeft("numberOfRecords2Save:", 20)   << "  "  << numberOfRecords2Save) );
    response_lines.push_back(MTK_SS(s_AlignLeft("frecuency:"			  , 20)   << "  "  << frecuency) );
    response_lines.push_back(MTK_SS(s_AlignLeft("warningOnQueueSize:"  , 20)   << "  "  << warningOnQueueSize) );
    response_lines.push_back(MTK_SS(s_AlignLeft("errorOnQueueSize:"	  , 20)   << "  "  << errorOnQueueSize) );
    response_lines.push_back(MTK_SS(s_AlignLeft("maxTime2saveRecods:"  , 20)   << "  "  << maxTime2saveRecods) );
}
//----------------------------------------------------------------------------------------------------------------
void fbInsert::command_stats (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("fbi." << mtk::s_toLower(fbi_config) << ".stats:  ----------------------"));
    response_lines.push_back(MTK_SS(s_AlignLeft("prepare:"			 , 20)   << "  "  << prepare) );
    response_lines.push_back(MTK_SS(s_AlignLeft("queue.size:"		 , 20)   << "  "  << queue.size()) );
    response_lines.push_back(MTK_SS(s_AlignLeft("savedRecords:"		 , 20)   << "  "  << savedRecords) );
    response_lines.push_back(MTK_SS(s_AlignLeft("receivedRecords:"    , 20)   << "  "  << receivedRecords) );
}
//----------------------------------------------------------------------------------------------------------------
void fbInsert::command_status (const std::string& /*command*/, const std::string& /*params*/, mtk::list<std::string>&  response_lines)
{
    response_lines.push_back(MTK_SS("fbi." << mtk::s_toLower(fbi_config) << ".status:  ----------------------"));
    
    
		if (db->Connected()	)
            response_lines.push_back(MTK_SS(s_AlignLeft("Connected:"			   , 22)  << "  true" ) );
		else
            response_lines.push_back(MTK_SS(s_AlignLeft("Connected:"			   , 22)  << "  false") );

        if (dbConnectionErrorSent)
            response_lines.push_back(MTK_SS(s_AlignLeft("dbConnectionErrorSent:", 22)  << "  true" ) );
		else
            response_lines.push_back(MTK_SS(s_AlignLeft("dbConnectionErrorSent:", 22)  << "  false") );

        response_lines.push_back(MTK_SS(s_AlignLeft("Received Records:"  , 22)  << "  "  << receivedRecords) );
        response_lines.push_back(MTK_SS(s_AlignLeft("Received Records:"  , 22)  << "  "  << savedRecords) );
}
//----------------------------------------------------------------------------------------------------------------


void fbInsert::command_set_frecuency(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    bool result;
    mtk::dtTimeQuantity resulttq(mtk::dtSeconds(0));
    mtk::s_TRY_stotq(mtk::s_trim(params, ' '), mtk::dtSeconds(0)).assign(resulttq, result);
    if (result)
    {
        frecuency = resulttq;
        response_lines.push_back(MTK_SS("fbi." << fbi_config  << ".SetFrecuency:  ----------------------"));
        response_lines.push_back("frecuency change ok. The change is not persistent");
    }
    else
        response_lines.push_back("ERROR: frecuency not changed. Espected a timequantity format");
}

//-------------------------------------------------------

void fbInsert::command_set_error_on_queue_size(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    bool result;
    int resultint;
    mtk::s_TRY_stoi(mtk::s_trim(params, ' '),0).assign(resultint, result);

    if (result)
    {
        errorOnQueueSize = resultint;
        response_lines.push_back(MTK_SS("fbi." << fbi_config  << ".SetErrorOnQueueSize:  ----------------------"));
        response_lines.push_back("errorOnQueueSize changed. The change is not persistent");
    }
    else
        response_lines.push_back("ERROR: errorOnQueueSize not changed. Espected an integer");
}

//-------------------------------------------------------

void fbInsert::command_set_warning_queue_size(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    bool result;
    int resultint;
    mtk::s_TRY_stoi(mtk::s_trim(params, ' '),0).assign(resultint, result);

    if (result)
    {
        warningOnQueueSize = resultint;
        response_lines.push_back(MTK_SS("fbi." << fbi_config  << ".SetWarningOnQueueSize:  ----------------------"));
        response_lines.push_back("warningOnQueueSize changed ok. The change is not persistent");
    }
    else
        response_lines.push_back("ERROR: warningOnQueueSize not changed. Espected an integer");
}

//-------------------------------------------------------

void fbInsert::command_set_max_time2save_records(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    bool result;
    mtk::dtTimeQuantity resulttq(mtk::dtSeconds(0));
    mtk::s_TRY_stotq(mtk::s_trim(params, ' '), mtk::dtSeconds(0)).assign(resulttq, result);
    if (result)
    {
        maxTime2saveRecods = resulttq;
        response_lines.push_back(MTK_SS("fbi." << fbi_config  << ".SetMaxTime2saveRecods:  ----------------------"));
        response_lines.push_back("maxTime2saveRecods changed ok. The change is not persistent");
    }
    else
        response_lines.push_back("ERROR: maxTime2saveRecods not changed. Espected an integer");
}

//-------------------------------------------------------

void fbInsert::command_set_number_of_records2save(const std::string& /*command*/, const std::string& params, mtk::list<std::string>&  response_lines)
{
    bool result;
    int resultint;
    mtk::s_TRY_stoi(mtk::s_trim(params, ' '),0).assign(resultint, result);

    if (result)
    {
        numberOfRecords2Save = resultint;
        response_lines.push_back(MTK_SS("fbi." << fbi_config  << ".setNumberOfRecords2Save:  ----------------------"));
        response_lines.push_back("numberOfRecords2Save changed ok. The change is not persistent");
    }
    else
        response_lines.push_back("ERROR: numberOfRecords2Save not changed. Espected an integer");
}


//-------------------------------------------------------


fbInsert::fbInsert(const std::string& _fbi_config, const std::string& _prepare)
    :     numberOfRecords2Save                      (mtk::s_fbNumberOfRecords2SaveFromConfig(MTK_SS(_fbi_config << ".CONTROL")))
        , frecuency                                 (mtk::s_fbFrecuencyFromConfig           (MTK_SS(_fbi_config << ".CONTROL")))
        , warningOnQueueSize                        (mtk::s_fbWarningOnQueueSizeFromConfig  (MTK_SS(_fbi_config << ".CONTROL")))
        , errorOnQueueSize                          (mtk::s_fbErrorOnQueueSizeFromConfig    (MTK_SS(_fbi_config << ".CONTROL")))
        , maxTime2saveRecods                        (mtk::s_fbMaxTime2saveRecodsFromConfig  (MTK_SS(_fbi_config << ".CONTROL")))
        , db                                        (mtk::fbDatabaseFromConfig              (_fbi_config                      ))
        , prepare                                   (_prepare)
        , savedRecords                              (0)
        , receivedRecords                           (0)
		, dbConnectionErrorSent						(false)
        , fbi_config                                (_fbi_config)
{
	db->Connect();


    std::string instance_uuid = MTK_SS("fbi." << fbi_config);
    MTK_CONNECT_THIS(*mtk::admin::register_command("__GLOBAL__",  "config", ""),                            command_config);
    MTK_CONNECT_THIS(*mtk::admin::register_command(instance_uuid, "config", ""),                            command_config);
    MTK_CONNECT_THIS(*mtk::admin::register_command("__GLOBAL__",  "stats", ""),                             command_stats);
    MTK_CONNECT_THIS(*mtk::admin::register_command(instance_uuid, "stats", ""),                             command_stats);
    
    MTK_CONNECT_THIS(*mtk::admin::register_command(instance_uuid, "status", ""),                            command_status);
    MTK_CONNECT_THIS(*mtk::admin::register_command(instance_uuid, "set_frecuency", "",              true),  command_set_frecuency);
    MTK_CONNECT_THIS(*mtk::admin::register_command(instance_uuid, "set_error_on_queue_size", "",    true),  command_set_error_on_queue_size);
    MTK_CONNECT_THIS(*mtk::admin::register_command(instance_uuid, "set_wargning_on_queue_size", "", true),  command_set_warning_queue_size);
    MTK_CONNECT_THIS(*mtk::admin::register_command(instance_uuid, "set_max_time2save_records", "",  true),  command_set_max_time2save_records);
    MTK_CONNECT_THIS(*mtk::admin::register_command(instance_uuid, "set_num_records2save", "",       true),  command_set_number_of_records2save);
    

    MTK_TIMER_1D(OnTimer);
}
//----------------------------------------------------------------------------------------------------------------
fbInsert::~fbInsert(void)
{
	//if (dbConnectionErrorSent)
	//	 pending mtk::Admin::i()->NotifyAlarmStatusStop("Problems with database");

	if (db->Connected())
		db->Disconnect();
}

//----------------------------------------------------------------------------------------------------------------
void fbInsert::Insert(const fbInsertParams& params)
{
    ++receivedRecords;
    queue.push_back(params);

    //  Aviso ERROR muchos mensajes por escribir grande

	if (int(queue.size()) > errorOnQueueSize)
	{
		MTK_EXEC_MAX_FREC( mtk::dtSeconds(59) )
            mtk::AlarmMsg(mtk::Alarm (
                                MTK_HERE, "fbInsert.Insert",
                                MTK_SS("Too many messages to write " <<  queue.size()),
                                mtk::alPriorError,
                                mtk::alTypeNoPermisions
                            )
            );
		MTK_END_EXEC_MAX_FREC
	}

    //  Aviso warning muchos mensajes por escribir grande
	if (int(queue.size()) > warningOnQueueSize)
	{
		MTK_EXEC_MAX_FREC( mtk::dtMinutes(2) )
            mtk::AlarmMsg(mtk::Alarm (
                                MTK_HERE, "fbInsert.Insert",
                                MTK_SS("Too many messages to write " <<  queue.size()),
                                mtk::alPriorWarning,
                                mtk::alTypeNoPermisions
                            )
            );
		MTK_END_EXEC_MAX_FREC
	}
}

//----------------------------------------------------------------------------------------------------------------

IBPP::Transaction fbInsert::TryStartTransaction(void)
{
	IBPP::Transaction result;
	try
	{
		result = IBPP::TransactionFactory(db);
		result->Start();
	}
	catch(...)
	{
		if (dbConnectionErrorSent == false)
		{
			dbConnectionErrorSent = true;
            /*   PENDING
			mtk::Admin::i()->NotifyAlarmStatus("Problems with database",
													mtk::Alarm (
														"fbInsert.TryStartTransaction",
														"problems with database",
														mtk::alPriorError,
														mtk::alTypeRealTime
													)
											  );
            */
		}
		//	db could be disconnected
		db->Disconnect();
		db->Connect();
		result = IBPP::TransactionFactory(db);
		result->Start();
	}
	if (dbConnectionErrorSent)
	{
		dbConnectionErrorSent = false;
		//pending  mtk::Admin::i()->NotifyAlarmStatusStop("Problems with database");
	}
	return result;
}

//----------------------------------------------------------------------------------------------------------------

void fbInsert::OnTimer(void)
{
    if (queue.size() == 0)      return;
    
	MTK_EXEC_MAX_FREC(frecuency)

		IBPP::Transaction tr = TryStartTransaction();

		try{
			IBPP::Statement st = IBPP::StatementFactory(db, tr);
			st->Prepare(prepare);

			//  durante un ratito intentamos guardar los registros configurados
			mtk::dtDateTime start = mtk::dtNowLocal();
			for (int contador=0; contador<numberOfRecords2Save; ++contador)
			{
				if (queue.size() == 0)      break;

				fbInsertParams params2Add = queue.front();
				queue.pop_front();

				//  guardamos un registro
				++savedRecords;
				int i=0;
				while (params2Add.lParams.size() > 0)
				{
					++i;
					__internal_fbInsertData field= params2Add.lParams.front();
					params2Add.lParams.pop_front();
					switch (field.dataType)
					{
						case __internal_fbInsertData::__fbidtNull:
										st->SetNull(i);
										break;
						case __internal_fbInsertData::__fbidtBool:
										st->Set(i, field.bValue);
										break;
						case __internal_fbInsertData::__fbidtString:
										st->Set(i, field.sValue);
										break;
						case __internal_fbInsertData::__fbidtInt:
										st->Set(i, field.iValue);
										break;
						case __internal_fbInsertData::__fbidtDouble:
										st->Set(i, field.dValue);
										break;
						case __internal_fbInsertData::__fbidtDateTime:
										if (field.dtValue.HasValue())
											st->Set(i, field.dtValue.Get());
										else
											st->SetNull(i);
										break;
						case __internal_fbInsertData::__fbidtTimeQuantity:
										if (field.dtValue.HasValue())
											st->Set(i, field.tqValue.Get());
										else
											st->SetNull(i);
										break;
												break;
						default:
									mtk::AlarmMsg(mtk::Alarm (
														MTK_HERE, "fbInsert.Insert",
														MTK_SS("unkown type " << int(field.dataType)),
														mtk::alPriorError,
														mtk::alTypeNoPermisions
													)
									);
					}
				}
				st->Execute();


				//  verificamos que no llevemos demasiado tiempo intentando guardar, en otro caso, esperamos a otro momento posterior
				if ((mtk::dtNowLocal() - start)  >  maxTime2saveRecods)
				{
				    MTK_EXEC_MAX_FREC_A( mtk::dtSeconds(20), A)
									mtk::AlarmMsg(mtk::Alarm (
												MTK_HERE, "fbInsert.Saving",
												MTK_SS("Too slow saving, delaying qs:" <<  queue.size()),
												mtk::alPriorWarning,
												mtk::alTypeNoPermisions
											)
							);
					MTK_END_EXEC_MAX_FREC
					break;
				}
			}
		}
		catch(...)
		{
			tr->Commit();
            queue.clear();
			throw;
		}

		tr->Commit();

	MTK_END_EXEC_MAX_FREC

}

};      //  namespace idt

