(this.webpackJsonpweb=this.webpackJsonpweb||[]).push([[0],{14:function(e,n,t){e.exports=t(27)},19:function(e,n,t){},21:function(e,n,t){},27:function(e,n,t){"use strict";t.r(n);var r=t(1),a=t.n(r),c=t(9),o=t.n(c),s=(t(19),t(2)),i=t.n(s),u=t(3),l=(t(21),t(4));function h(e){console.error(e)}function f(e){e=JSON.parse(e),console.log(e,typeof e);var n,t="",r=Object(l.a)(e.lines);try{for(r.s();!(n=r.n()).done;){var a=n.value;t+="p,";var c,o=Object(l.a)(a.points);try{for(o.s();!(c=o.n()).done;){var s=c.value;t+="".concat(Math.round(s.x),",").concat(Math.round(s.y),",")}}catch(i){o.e(i)}finally{o.f()}t+="l,"}}catch(i){r.e(i)}finally{r.f()}return t}function p(e){return((e.match(/,/g)||[]).length-((e.match(/l/g)||[]).length+(e.match(/p/g)||[]).length))%2===1}function d(e){for(var n=e.length,t=[],r=0,a=502;r<n;){if(a>n)a=n;else for(;","!==e.charAt(a-1)||p(e.substring(r,a));)if(--a<=r)return console.log("ERROR"),null;t.push(e.substring(r,a)),r=a,a+=502}return t}function g(e,n,t){return v.apply(this,arguments)}function v(){return(v=Object(u.a)(i.a.mark((function e(n,t,r){var a,c,o;return i.a.wrap((function(e){for(;;)switch(e.prev=e.next){case 0:if(!((a="".concat(t,",").concat(r,",").concat(n)).length>512)){e.next=3;break}return e.abrupt("return",{success:!1,response:"request too large"});case 3:return e.prev=3,console.log("Sending data string:",a),e.next=7,fetch("".concat("","/points"),{method:"POST",body:a}).then((function(e){return e.text()}));case 7:return c=e.sent,o={success:!0,response:c},e.abrupt("return",o);case 12:e.prev=12,e.t0=e.catch(3),h(e.t0);case 15:case"end":return e.stop()}}),e,null,[[3,12]])})))).apply(this,arguments)}var b=t(13),m=function(){var e;function n(){return(n=Object(u.a)(i.a.mark((function n(){var t,r,a,c;return i.a.wrap((function(n){for(;;)switch(n.prev=n.next){case 0:if(!e){n.next=13;break}t=!1,r=d(f(e.getSaveData())),a=0;case 4:if(!(a<r.length)){n.next=12;break}return n.next=7,g(r[a],a,r.length);case 7:c=n.sent,t&=c.success;case 9:a++,n.next=4;break;case 12:t?e.clear():alert("there was an error in sending your points");case 13:case"end":return n.stop()}}),n)})))).apply(this,arguments)}return a.a.createElement("div",null,a.a.createElement(b.a,{hideInterface:!0,hideGrid:!0,lazyRadius:0,brushRadius:1,canvasWidth:1e3,canvasHeight:700,ref:function(n){return e=n}}),a.a.createElement("button",{onClick:function(){return n.apply(this,arguments)}},"send"),a.a.createElement("button",{onClick:function(){e&&e.clear()}},"clear"))};Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));o.a.render(a.a.createElement(m,null),document.getElementById("root")),"serviceWorker"in navigator&&navigator.serviceWorker.ready.then((function(e){e.unregister()})).catch((function(e){console.error(e.message)}))}},[[14,1,2]]]);
//# sourceMappingURL=main.97bbb74e.chunk.js.map