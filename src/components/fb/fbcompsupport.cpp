#include "fbcompsupport.h"


#include "components/admin/admin.h"





namespace mtk
{





IBPP::Database  	fbDatabaseFromConfig(const std::string& configPath)
{

	std::string path = configPath;
	mtk::Nullable<std::string> server = mtk::admin::get_config_property(MTK_SS(path << "." << "server"));
	mtk::Nullable<std::string> name = mtk::admin::get_config_property(MTK_SS(path << "." << "name"));
	mtk::Nullable<std::string> user = mtk::admin::get_config_property(MTK_SS(path << "." << "user"));
	std::string password;
	if (mtk::admin::is_production())
		password = "production";
	else
		password = "pruebas";

	if(server.HasValue() == false  ||  name.HasValue()==false  ||  user.HasValue()==false)
		throw
					mtk::Alarm (
						MTK_HERE, "fbDatabaseFromConfig",
						MTK_SS("mising server, name or user in config  from path " <<  configPath),
						mtk::alPriorCritic,
						mtk::alTypeNoPermisions
					);


	return IBPP::DatabaseFactory(server.Get(), name.Get(), user.Get(), password);

}







};  //	namespace idt
