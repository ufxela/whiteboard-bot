(this.webpackJsonpweb=this.webpackJsonpweb||[]).push([[0],{14:function(e,n,t){e.exports=t(27)},19:function(e,n,t){},21:function(e,n,t){},27:function(e,n,t){"use strict";t.r(n);var r=t(1),a=t.n(r),o=t(9),c=t.n(o),s=(t(19),t(2)),i=t.n(s),u=t(3),l=(t(21),t(4));function f(e){console.error(e)}function p(e){e=JSON.parse(e),console.log(e,typeof e);var n,t=Object(l.a)(e.lines);try{for(t.s();!(n=t.n()).done;){var r,a=n.value,o=Object(l.a)(a.points);try{for(o.s();!(r=o.n()).done;){var c=r.value;console.log("point",c)}}catch(s){o.e(s)}finally{o.f()}}}catch(s){t.e(s)}finally{t.f()}return"unimplemented"}function h(e){return d.apply(this,arguments)}function d(){return(d=Object(u.a)(i.a.mark((function e(n){var t,r;return i.a.wrap((function(e){for(;;)switch(e.prev=e.next){case 0:return e.prev=0,console.log("Sending points string:",n),e.next=4,fetch("".concat("","/points"),{method:"post",body:n}).then((function(e){return e.text()}));case 4:return t=e.sent,console.log(t),r={success:!0,response:t},e.abrupt("return",r);case 10:e.prev=10,e.t0=e.catch(0),f(e.t0);case 13:case"end":return e.stop()}}),e,null,[[0,10]])})))).apply(this,arguments)}var v=t(13),m=function(){var e;function n(){return(n=Object(u.a)(i.a.mark((function n(){return i.a.wrap((function(n){for(;;)switch(n.prev=n.next){case 0:if(!e){n.next=5;break}return n.next=3,h(p(e.getSaveData()));case 3:n.sent.success?e.clear():alert("there was an error in sending your points");case 5:case"end":return n.stop()}}),n)})))).apply(this,arguments)}return a.a.createElement("div",null,a.a.createElement(v.a,{hideInterface:!0,hideGrid:!0,lazyRadius:0,brushRadius:1,canvasWidth:1e3,canvasHeight:700,ref:function(n){return e=n}}),a.a.createElement("button",{onClick:function(){return n.apply(this,arguments)}},"send"),a.a.createElement("button",{onClick:function(){e&&e.clear()}},"clear"))};Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));c.a.render(a.a.createElement(m,null),document.getElementById("root")),"serviceWorker"in navigator&&navigator.serviceWorker.ready.then((function(e){e.unregister()})).catch((function(e){console.error(e.message)}))}},[[14,1,2]]]);
//# sourceMappingURL=main.57681b0b.chunk.js.map