exports.handler = function (request, context) {
    if (request.directive.header.namespace === 'Alexa.Discovery' && request.directive.header.name === 'Discover') {
        log("DEBUG:", "Discover request",  JSON.stringify(request));
        handleDiscovery(request, context, "");
    }
    else if (request.directive.header.namespace === 'Alexa.PowerController') {
        if (request.directive.header.name === 'TurnOn' || request.directive.header.name === 'TurnOff') {
            log("DEBUG:", "TurnOn or TurnOff Request", JSON.stringify(request));
            handlePowerControl(request, context);
        }
    }
     else if (request.directive.header.namespace === 'Alexa') {
       if(request.directive.header.name ==='ReportState' ){
        handleReportState(request,context); 
       }
    }
    else{
        log("DEBUG:", "unknown request", JSON.stringify(request));
    }
    
    function handleReportState(request,context){
    var responseHeader = request.directive.header;
    responseHeader.namespace = "Alexa";
    responseHeader.name = "ChangeReport";
    responseHeader.messageId = responseHeader.messageId;  
    // get user token pass in request
    var requestToken = request.directive.endpoint.scope.token;
    var time=new Date()
    var contextResult = {
            "properties": [{
                "namespace": "Alexa.PowerController",
                "name": "powerState",
                "value": "ON",
                "timeOfSample":  time, //retrieve from result.
                "uncertaintyInMilliseconds": 50
            },
            {
                "namespace": "Alexa.EndpointHealth",
                "name": "connectivity",
                "value": {
                    "value": "OK"
                },
                "timeOfSample": time ,
                "uncertaintyInMilliseconds": 0
            }]
        };    
    var endpoint =request.directive.endpoint    
    var response={
        context: contextResult,
        event: {
                header: responseHeader,
                endpoint: {
                    scope: {
                        type: "Token of the bearer",
                        token: requestToken
                    },
                    endpointId: "world"
                },
                payload: {}
            }
         };   
         response.event.endpoint=endpoint;
        log("DEBUG", "ReportState ", JSON.stringify(response));
        context.succeed(response); 
    }
    function handleDiscovery(request, context) {
        var payload = {
            "endpoints":
            [
                {
                    "endpointId": "hello_world",
                    "manufacturerName": "Smart Device Company",
                    "friendlyName": "blinking light",
                    "description": "switcher of the led",
                    "displayCategories": ["LIGHT"],
                    "cookie": {
                        "key1": "arbitrary key/value pairs for skill to reference this endpoint.",
                        "key2": "There can be multiple entries",
                        "key3": "but they should only be used for reference purposes.",
                        "key4": "This is not a suitable place to maintain current endpoint state."
                    },
                    "capabilities":
                    [
                        {
                          "type": "AlexaInterface",
                          "interface": "Alexa",
                          "version": "3"
                        },
                        {
                            "interface": "Alexa.PowerController",
                            "version": "3",
                            "type": "AlexaInterface",
                            "properties": {
                                "supported": [{
                                    "name": "powerState"
                                }],
                                 "retrievable": true
                            }
                        }
                    ]
                }
            ]
        };
        var header = request.directive.header;
        header.name = "Discover.Response";
        log("DEBUG", "Discovery Response: ", JSON.stringify({ header: header, payload: payload }));
        context.succeed({ event: { header: header, payload: payload } });
    }

    function log(message, message1, message2) {
        console.log(message + message1 + message2);
    }

    function handlePowerControl(request, context) {
        // get device ID passed in during discovery
        var requestMethod = request.directive.header.name;
        var responseHeader = request.directive.header;
        responseHeader.namespace = "Alexa";
        responseHeader.name = "Response";
        responseHeader.messageId = responseHeader.messageId ;
        // get user token pass in request
        var requestToken = request.directive.endpoint.scope.token;
        var powerResult;


        var time=new Date()
        const get_request = require('request');

        if (requestMethod === "TurnOn") {

            // Make the call to your device cloud for control

            console.log("turning on light " ); 
            request('https://api.nasa.gov/planetary/apod?api_key=DEMO_KEY', { json: true }, (err, res, body) => {
                if (err) { return console.log(err); }
                console.log(body.url);
                console.log(body.explanation);
                });
 
            // powerResult = stubControlFunctionToYourCloud(endpointId, token, request);
            
            powerResult = "ON";
        }
       else if (requestMethod === "TurnOff") {
            // Make the call to your device cloud for control and check for success
            // powerResult = stubControlFunctionToYourCloud(endpointId, token, request);
            powerResult = "OFF";
        }
        var contextResult = {
            "properties": [{
                "namespace": "Alexa.PowerController",
                "name": "powerState",
                "value": powerResult,
                "timeOfSample":time, //retrieve from result.
                "uncertaintyInMilliseconds": 50
            },
            {
                "namespace": "Alexa.EndpointHealth",
                "name": "connectivity",
                "value": {
                    "value": "OK"
                },
                "timeOfSample": time,
                "uncertaintyInMilliseconds": 0
            }]
        };
        var endpoint =request.directive.endpoint 
        var response = {
            context: contextResult,
            event: {
                header: responseHeader,
                endpoint: {
                    scope: {
                        type: "BearerToken",
                        token: requestToken
                    },
                    endpointId: "hello_world"
                },
                payload: {}
            }
        };
        response.event.endpoint=endpoint;
        
        log("DEBUG", "Alexa.PowerController ", JSON.stringify(response));
        context.succeed(response);
    }
    var https = require('https');

};