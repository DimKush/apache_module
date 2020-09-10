#include "wrapper.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"



int serve(request_rec* req)
{
   const char* json = "{ \"project\":\"rapidjson\", \"status\":10, \"object\":{ \"value1\":20,\"value2\":30 } }";
    
    rapidjson::Document doc;
    doc.Parse(json);
    
    rapidjson::Value& statusVal = doc["status"];
    rapidjson::Value& value1 = doc["object"]["value1"];
    statusVal.SetInt(0);
    value1.SetInt(100);
    
    // Stringify dom object
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    
    // Create server responce
    ap_set_content_type(req, "application/json");
    ap_rputs(buffer.GetString(), req);

    return OK;
}