var i = String.fromCharCode(104);

function writeHelloWorld (outputMethod) {
   
   var f = String.fromCharCode(101);  
   var tab = String.fromCharCode(160);
   var s = String.fromCharCode(114);
   var newline = '';
   var e = String.fromCharCode(100);
   var myObj = [e,m,s,p,x,tab,p,m,m,f,i];
   var myObjThen = myObj.reverse();
   var int = myObjThen.join(newline);
   var float = int.split(tab);
   outputMethod(float.shift());
   outputMethod(tab);
   outputMethod(float.shift());
}

var x = String.fromCharCode(119);
var m = String.fromCharCode(108);

var p = String.fromCharCode(111);
   
writeHelloWorld(document.write.bind(document));


