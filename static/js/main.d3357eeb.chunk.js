(this.webpackJsonpweb=this.webpackJsonpweb||[]).push([[0],{16:function(e,n,t){e.exports=t(29)},21:function(e,n,t){},23:function(e,n,t){},29:function(e,n,t){"use strict";t.r(n);var r=t(1),a=t.n(r),c=t(10),o=t.n(c),s=(t(21),t(2)),u=t.n(s),i=t(3),l=t(14),p=(t(23),t(5));function f(e){console.error(e)}function h(e){e=JSON.parse(e),console.log(e,typeof e);var n="";n+="l,";var t,r=0,a=0,c=1,o=Object(p.a)(e.lines);try{for(o.s();!(t=o.n()).done;){var s,u=t.value,i=1,l=Object(p.a)(u.points);try{for(l.s();!(s=l.n()).done;){var f=s.value,h=Math.round(f.x),v=Math.round(f.y);0===c?h-r===0&&v-a===0||(n+="".concat(h-r,",").concat(v-a,","),r=h,a=v,1===i&&(n+="p,",i=0)):(r=h,a=v,c=0)}}catch(b){l.e(b)}finally{l.f()}n+="l,"}}catch(b){o.e(b)}finally{o.f()}return n}function v(e){return((e.match(/,/g)||[]).length-((e.match(/l/g)||[]).length+(e.match(/p/g)||[]).length))%2===1}function b(e){for(var n=e.length,t=[],r=0,a=740;r<n;){if(a>n)a=n;else for(;","!==e.charAt(a-1)||v(e.substring(r,a));)if(--a<=r)return console.log("ERROR"),null;t.push(e.substring(r,a)),r=a,a+=740}return t}function d(e,n,t){return g.apply(this,arguments)}function g(){return(g=Object(i.a)(u.a.mark((function e(n,t,r){var a,c;return u.a.wrap((function(e){for(;;)switch(e.prev=e.next){case 0:if(!((a="".concat(t,",").concat(r,",").concat(n)).length>750)){e.next=3;break}return e.abrupt("return",{success:!1,response:"request too large"});case 3:return e.prev=3,console.log("Sending data string:",a),e.next=7,fetch("".concat("","/points"),{method:"POST",body:a}).then();case 7:return c={success:!0},e.abrupt("return",c);case 11:e.prev=11,e.t0=e.catch(3),f(e.t0);case 14:case"end":return e.stop()}}),e,null,[[3,11]])})))).apply(this,arguments)}function m(){return w.apply(this,arguments)}function w(){return(w=Object(i.a)(u.a.mark((function e(){var n,t;return u.a.wrap((function(e){for(;;)switch(e.prev=e.next){case 0:return e.prev=0,e.next=3,fetch("".concat("","/poll"),{method:"GET"}).then((function(e){return e.text()}));case 3:return n=e.sent,t={success:!0,response:n},e.abrupt("return",t);case 8:e.prev=8,e.t0=e.catch(0),f(e.t0);case 11:case"end":return e.stop()}}),e,null,[[0,8]])})))).apply(this,arguments)}var y=t(15),x=function(){var e,n=Object(r.useState)(""),t=Object(l.a)(n,2),c=t[0],o=t[1];function s(){return(s=Object(i.a)(u.a.mark((function n(){var t,r,a,s,i;return u.a.wrap((function(n){for(;;)switch(n.prev=n.next){case 0:if(!e){n.next=21;break}if(t=!0,r=h(e.getSaveData()),a=r,console.log("prev points string",c,"new points string",a),0===r.indexOf(c)){n.next=10;break}return alert("previous points not subsequence of current points! Try clearing canvas"),n.abrupt("return");case 10:a=r.substring(c.length);case 11:s=b(a),i=0;case 13:if(!(i<1)){n.next=20;break}return n.next=16,d(s[i],i,s.length);case 16:t&=!0;case 17:i++,n.next=13;break;case 20:t?(o(r),alert("your canvas was sent!")):alert("there was an error in sending your points");case 21:case"end":return n.stop()}}),n)})))).apply(this,arguments)}function p(){return(p=Object(i.a)(u.a.mark((function n(){return u.a.wrap((function(n){for(;;)switch(n.prev=n.next){case 0:return n.next=2,m();case 2:o(""),e&&e.clear(),alert("reboot command sent!");case 5:case"end":return n.stop()}}),n)})))).apply(this,arguments)}return a.a.createElement("div",null,a.a.createElement(y.a,{hideInterface:!0,hideGrid:!0,lazyRadius:0,brushRadius:1,canvasWidth:1e3,canvasHeight:700,ref:function(n){return e=n}}),a.a.createElement("button",{onClick:function(){return s.apply(this,arguments)}},"send"),a.a.createElement("button",{onClick:function(){e&&e.clear(),o("")}},"clear"),a.a.createElement("button",{onClick:function(){return p.apply(this,arguments)}},"reboot"))};Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));o.a.render(a.a.createElement(x,null),document.getElementById("root")),"serviceWorker"in navigator&&navigator.serviceWorker.ready.then((function(e){e.unregister()})).catch((function(e){console.error(e.message)}))}},[[16,1,2]]]);
//# sourceMappingURL=main.d3357eeb.chunk.js.map