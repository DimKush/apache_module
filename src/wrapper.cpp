#include "wrapper.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"



int serve(request_rec* req)
{
   const char* json = "{\"project\":\"rapidjson\",\"status\":10}";
    
    rapidjson::Document doc;
    doc.Parse(json);
    
    rapidjson::Value& statusVal = doc["status"];
    statusVal.SetInt(0);

    // Stringify dom object
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    // Create server responce
    ap_set_content_type(req, "application/json");
    ap_rputs(buffer.GetString(), req);

    return OK;
}