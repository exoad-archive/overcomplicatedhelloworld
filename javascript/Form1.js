//source: https://codegolf.stackexchange.com/a/40195

(function(context){
    /**
     * Basic app configuration
    */
    var config = {
        DEBUG:            true,
        WRITER_SIGNATURE: "write",
        LANGUAGE:         "en-US" // default language
    };

    /**
     * Hardcoded translation data
    */
    var translationData = {
        "en-US": {
            "hello_world":       "Hello World!", // greeting in main view
            "invocation":        "invoked", // date of invokation
            "styled_invocation": "[%str%]" // some decoration for better style
        }
    };

    /**
     * Internationalization module
     * Supports dynamic formatting and language pick after load
    */
    var i18n = (function(){
        return {
            format: function(source, info){ // properly formats a i18n resource
                return source.replace("%str%", info);
            },
            originTranslate: function(origin){
                var invoc_stf = i18n.translate("invocation") + " " + origin.lastModified;
                return i18n.format(i18n.translate("styled_invocation"), invoc_stf);
            },
            translate: function(message){
                var localData = translationData[config.LANGUAGE];
                return localData[message];
            },
            get: function(message, origin){
                var timestamp = origin.lastModified;
                if(config.DEBUG)
                    return i18n.translate(message) + " " + i18n.originTranslate(origin);
                else
                    return i18n.translate(message);
            }
        };
    }());

    /**
     * A clone of a document-wrapper containing valid, ready DOM
    */
    var fallbackDocument = function(){
        var _document = function(){
            this.native_context = context;
            this.modules = new Array();
        };
        _document.prototype.clear = function(){
            for(var i = 0; i < this.modules.length; i++){
                var module = this.modules[i];
                module.signalClear();
            };
        };

        return _document;
    };

    /**
     * Provides a native document, scoped to the context
     * Uses a fallback if document not initialized or not supported
    */
    var provideDocument = function(){
        if(typeof context.document == "undefined")
            context.document = new fallbackDocument();
        context.document.lastModified = new context.Date();
        context.document.exception = function(string_exception){
            this.origin = context.navigator;
            this.serialized = string_exception;
        };

        return context.document;
    };

    /**
     * Sends a data request, and tries to call the document writer
    */
    var documentPrinter = function(document, dataCallback){
        if(dataCallback == null)
            throw new document.exception("Did not receive a data callback!");
        data = i18n.get(dataCallback(), document); // translate data into proper lang.
        if(typeof document[config.WRITER_SIGNATURE] == "undefined")
            throw new document.exception("Document provides no valid writer!");

        var writer = document[config.WRITER_SIGNATURE]; 
        writer.apply(document, [data]); //apply the writer using correct context
    };

    /**
     * Produces a "Hello world" message-box
     * Warning! Message may vary depending on initial configuration
    */
    var HelloWorldFactory = (function(){
        return function(){
            this.produceMessage = function(){
                this.validDocument = provideDocument();
                new documentPrinter(this.validDocument, function(){
                    return "hello_world";
                });
            };
        };
    }());

    context.onload = function(){ // f**k yeah! we are ready
        try{
        var newFactory = new HelloWorldFactory();
        newFactory.produceMessage();
        } catch(err){
            console.log(err); // silently log the error
        };
    };
}(window || {}));
