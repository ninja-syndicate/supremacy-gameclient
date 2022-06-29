/*! For license information please see mech.js.LICENSE.txt */
(()=>{var e={"./node_modules/behaviortree/lib/index.js":e=>{var t,s=Object.defineProperty,r=Object.defineProperties,o=Object.getOwnPropertyDescriptor,n=Object.getOwnPropertyDescriptors,a=Object.getOwnPropertyNames,i=Object.getOwnPropertySymbols,c=Object.prototype.hasOwnProperty,l=Object.prototype.propertyIsEnumerable,u=(e,t,r)=>t in e?s(e,t,{enumerable:!0,configurable:!0,writable:!0,value:r}):e[t]=r,d=(e,t)=>{for(var s in t||(t={}))c.call(t,s)&&u(e,s,t[s]);if(i)for(var s of i(t))l.call(t,s)&&u(e,s,t[s]);return e},T=(e,t)=>r(e,n(t)),h=(e,t)=>{var s={};for(var r in e)c.call(e,r)&&t.indexOf(r)<0&&(s[r]=e[r]);if(null!=e&&i)for(var r of i(e))t.indexOf(r)<0&&l.call(e,r)&&(s[r]=e[r]);return s},_=(e,t)=>{for(var r in t)s(e,r,{get:t[r],enumerable:!0})},p=(t="undefined"!=typeof WeakMap?new WeakMap:0,(e,r)=>t&&t.get(e)||(r=((e,t,r,n)=>{if(t&&"object"==typeof t||"function"==typeof t)for(let r of a(t))!c.call(e,r)&&s(e,r,{get:()=>t[r],enumerable:!(n=o(t,r))||n.enumerable});return e})(s({},"__esModule",{value:!0}),e),t&&t.set(e,r),r)),S={};_(S,{BehaviorTree:()=>R,BehaviorTreeImporter:()=>W,BranchNode:()=>V,Decorator:()=>O,FAILURE:()=>f,Introspector:()=>q,Node:()=>L,ObserverAborts:()=>U,Parallel:()=>K,ParallelComplete:()=>Z,ParallelSelector:()=>X,RUNNING:()=>b,Random:()=>D,SUCCESS:()=>v,Selector:()=>H,Sequence:()=>G,Task:()=>A,decorators:()=>M,default:()=>Y,getRegistry:()=>I,registryLookUp:()=>w});var b=Symbol("running"),v=!0,f=!1;function g(e){return e===b||"object"==typeof e&&e.total===b}var B=()=>!1,k=()=>!0,m=()=>{},y=()=>{},L=class{constructor(e){this.nodeType="Node",this.ranStart=!1;var t=e,{run:s=B,start:r=k,end:o=m,abort:n=y}=t,a=h(t,["run","start","end","abort"]);this.blueprint=d({run:s,start:r,end:o,abort:n},a)}run(e,t={}){var s=t,{introspector:r,rerun:o=!1,registryLookUp:n=(e=>e)}=s,a=h(s,["introspector","rerun","registryLookUp"]);if(!o||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===f)return t}let i=this.blueprint.run(e,T(d({},a),{rerun:o,registryLookUp:n}));return i!==b&&this.blueprint.end(e),r&&r.push(this,i,e),i}abort(e,{registryLookUp:t=(e=>e),lastRun:s}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:s})}get name(){return this._name||this.blueprint.name}set name(e){this._name=e}},A=class extends L{constructor(){super(...arguments),this.nodeType="Task"}},P={};function I(){return P}function w(e){if("string"==typeof e){let t=P[e];if(!t)throw new Error(`No node with name ${e} registered.`);return t}return e}var R=class{constructor({tree:e,blackboard:t}){this.tree=e,this.blackboard=t,this.lastResult=void 0}step({introspector:e}={}){let t=this.lastResult&&"object"==typeof this.lastResult?this.lastResult:void 0,s=g(this.lastResult);e&&e.start(this),this.lastResult=w(this.tree).run(this.blackboard,{lastRun:t,introspector:e,rerun:s,registryLookUp:w}),e&&e.end()}static register(e,t){P[e]="function"==typeof t?new A({name:e,run:t}):t}static cleanRegistry(){P={}}},M={};_(M,{AlwaysFailDecorator:()=>x,AlwaysSucceedDecorator:()=>j,CooldownDecorator:()=>N,InvertDecorator:()=>F,LoopDecorator:()=>Q});var C,U=((C=U||{})[C.None=0]="None",C[C.Self=1]="Self",C[C.LowerPriority=2]="LowerPriority",C[C.Both=3]="Both",C),E=e=>"observerAborts"in e,O=class extends L{constructor(e={config:{}}){var t=e,{config:s={}}=t;super(h(t,["config"])),this.nodeType="Decorator",this.observerAborts=0,this.setConfig(s)}condition(e){return v}decorate(e,t,s,r){return this.condition(t)||r&&1!==this.observerAborts&&3!==this.observerAborts?e(e,t,s):f}run(e,t={}){var s=t,{introspector:r,rerun:o,registryLookUp:n=(e=>e)}=s,a=h(s,["introspector","rerun","registryLookUp"]);if(!o||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===f)return t}let i=0,c=this.decorate((()=>(++i,n(this.blueprint.node).run(e,T(d({},a),{rerun:o,introspector:r,registryLookUp:n})))),e,this.config,o);return c!==b&&(this.blueprint.end(e),void 0!==(c===f&&this.blueprint.node)&&this.blueprint.node.blueprint.end(e)),r&&r.wrapLast(i,this,c,e),c}abort(e,{registryLookUp:t=(e=>e),lastRun:s}={}){super.abort(e,{registryLookUp:t,lastRun:s}),void 0!==this.blueprint.node&&this.blueprint.node.abort(e,{registryLookUp:t,lastRun:s})}setConfig(e){this.config=e}},x=class extends O{constructor(){super(...arguments),this.nodeType="AlwaysFailDecorator"}decorate(e){let t=e();return g(t)?t:f}},j=class extends O{constructor(){super(...arguments),this.nodeType="AlwaysSucceedDecorator"}decorate(e){let t=e();return g(t)?t:v}},N=class extends O{constructor(){super(...arguments),this.lock=!1,this.nodeType="CooldownDecorator"}setConfig({cooldown:e=5}){this.config={cooldown:e}}decorate(e){if(this.lock)return f;let t=e();return g(t)||(this.lock=!0,setTimeout((()=>{this.lock=!1}),1e3*this.config.cooldown)),t}},F=class extends O{constructor(){super(...arguments),this.nodeType="InvertDecorator"}decorate(e){let t=e();return g(t)?t:t===v?f:v}},Q=class extends O{constructor(){super(...arguments),this.nodeType="LoopDecorator"}setConfig({loop:e=1/0}){this.config={loop:e}}decorate(e){let t=0,s=f;for(;t++<this.config.loop;)if(s=e(),s===f)return f;return s}},V=class extends L{constructor(e){super(e),this.OPT_OUT_CASE=v,this.START_CASE=v,this.nodeType="BranchNode",this.nodes=e.nodes||[],this.numNodes=this.nodes.length,this.observedDecorators=new Map}run(e={},{lastRun:t,introspector:s,rerun:r,registryLookUp:o=(e=>e)}={}){if(!r||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===f)return t}let n=this.START_CASE,a=[],i="object"==typeof t&&t.state||[],c=Math.max(i.findIndex((e=>g(e))),0),l=0;for(;l<this.numNodes;++l){let t=!1;if(r&&this.observedDecorators.has(l))t=!0;else if(l<c){a[l]=i[l];continue}let u=o(this.nodes[l]);if(t&&E(u))if(this.observedDecorators.get(l)===u.condition(e)){if(r&&l<c){a[l]=i[l];continue}}else o(this.nodes[c]).abort(e,{registryLookUp:o,lastRun:i[c]}),c=0;let d=u.run(e,{lastRun:i[l],introspector:s,rerun:r,registryLookUp:o});if(a[l]=d,E(u)&&u.observerAborts>0&&this.observedDecorators.set(l,u.condition(e)),d===b||"object"==typeof d){n=b;break}if(d===this.OPT_OUT_CASE){n=d;break}r=!1}let u=g(n);if(u||this.blueprint.end(e),s){let t=u?b:n;s.wrapLast(Math.min(l+1,this.numNodes),this,t,e)}return n===b?{total:n,state:a}:n}abort(e={},{lastRun:t,registryLookUp:s=(e=>e)}={}){super.abort(e,{registryLookUp:s,lastRun:t});let r="object"==typeof t&&t.state||[],o=Math.max(r.findIndex((e=>g(e))),0);s(this.nodes[o]).abort(e,{registryLookUp:s,lastRun:r[o]})}},D=class extends V{constructor(){super(...arguments),this.nodeType="Random"}run(e={},{lastRun:t,introspector:s,rerun:r,registryLookUp:o=(e=>e)}={}){let n=0;r?n=t.state.findIndex((e=>g(e))):(this.blueprint.start(e),n=Math.floor(Math.random()*this.numNodes));let a=o(this.nodes[n]).run(e,{lastRun:t,introspector:s,rerun:r,registryLookUp:o}),i=g(a);if(i||this.blueprint.end(e),s){let t=i?b:a;s.wrapLast(1,this,t,e)}if(i){let e={total:b,state:new Array(this.numNodes).fill(void 0)};return e.state[n]=a,e}return a}},H=class extends V{constructor(){super(...arguments),this.nodeType="Selector",this.START_CASE=f,this.OPT_OUT_CASE=v}},G=class extends V{constructor(){super(...arguments),this.nodeType="Sequence",this.START_CASE=v,this.OPT_OUT_CASE=f}},W=class{constructor(){this.types={task:A,decorator:O,selector:H,sequence:G,random:D,invert:F,fail:x,succeed:j,cooldown:N,loop:Q}}defineType(e,t){this.types[e]=t}parse(e){let t=e,{type:s,name:r}=t,o=h(t,["type","name"]),n=this.types[s];if(!n){let e=w(s);if(e)return e.name=r,e;throw new Error(`Don't know how to handle type ${s}. Please register this first.`)}return new n({name:r,node:e.node?this.parse(e.node):null,nodes:e.nodes?e.nodes.map((e=>this.parse(e))):null,config:o})}},q=class{constructor(){this.currentResult=[],this.results=[]}start(e){this.tree=e,this.currentResult=[]}end(){let e=this.currentResult.pop();e&&this.results.push(e),delete this.tree,this.currentResult=[]}push(e,t,s){this.currentResult.push(this._toResult(e,t,s))}wrapLast(e,t,s,r){let o=this.currentResult.splice(this.currentResult.length-e,e);this.currentResult.push(T(d({},this._toResult(t,s,r)),{children:o}))}_toResult(e,t,s){return T(d({},e.name?{name:e.name}:{}),{result:t})}reset(){this.results=[]}get lastResult(){return 0===this.results.length?null:this.results[this.results.length-1]}},K=class extends V{constructor(e){super(e),this.nodeType="Parallel",this.nodes=e.nodes||[],this.numNodes=this.nodes.length}run(e={},{lastRun:t,introspector:s,rerun:r,registryLookUp:o=(e=>e)}={}){if(!r||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===f)return t}let n=[];for(let a=0;a<this.numNodes;++a){let i=t&&t.state[a];if(i&&!g(i)){n[a]=i;continue}let c=o(this.nodes[a]).run(e,{lastRun:i,introspector:s,rerun:r,registryLookUp:o});n[a]=c}let a=this.calcResult(n);if(g(a)||this.blueprint.end(e),s){let t=n.find((e=>g(e)))?b:a;s.wrapLast(this.numNodes,this,t,e)}return a}calcResult(e){return e.includes(f)?f:e.find((e=>g(e)))?{total:b,state:e}:v}abort(e,{registryLookUp:t=(e=>e),lastRun:s}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:s});for(let r of this.nodes)r.abort(e,{registryLookUp:t,lastRun:s})}},Z=class extends K{constructor(){super(...arguments),this.nodeType="ParallelComplete"}calcResult(e){return e.includes(f)?f:e.includes(v)?v:{total:b,state:e}}},X=class extends K{constructor(){super(...arguments),this.nodeType="ParallelSelector"}calcResult(e){return e.includes(f)?f:e.find((e=>g(e)))?{total:b,state:e}:v}},Y=R;e.exports=p(S)},"./src/branches/ParallelBackground.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.ParallelBackground=void 0;const r=s("./node_modules/behaviortree/lib/index.js");class o extends r.Parallel{constructor(){super(...arguments),this.nodeType="ParallelBackground"}run(e={},{lastRun:t,introspector:s,rerun:o,registryLookUp:c=(e=>e)}={}){const l=[];let u=!1;if(this.ranStart)for(let s=1;s<this.numNodes;++s){let o=t&&t.state[s];if(o&&i(o)){const t=c(this.nodes[s]).blueprint.start(e);if(t===r.FAILURE){l[s]=t,u=!0;break}}}if(!o||!this.ranStart){this.ranStart=!0;const t=this.blueprint.start(e);if(t===r.FAILURE)return t}if(!u)for(let r=0;r<this.numNodes;++r){let u=t&&t.state[r];if(u&&!n(u)){if(l[r]=u,0===r)break;if(a(u))break}const d=c(this.nodes[r]),T=!i(u)&&o,h=!i(u)&&u,_=d.run(e,{lastRun:h,introspector:s,rerun:T,registryLookUp:c});if(l[r]=_,0===r&&a(_))break}const d=this.calcResult(l);if((a(d)||i(l[0]))&&this.blueprint.end(e),s){const t=l.find((e=>n(e)))?r.RUNNING:d;s.wrapLast(this.numNodes,this,t,e)}return i(l[0])?r.SUCCESS:d}abort(e,{registryLookUp:t=(e=>e),lastRun:s}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:s});for(const r of this.nodes)r.abort(e,{registryLookUp:t,lastRun:s})}calcResult(e){return e.includes(r.FAILURE)?r.FAILURE:{total:r.RUNNING,state:e}}}function n(e){return e===r.RUNNING||"object"==typeof e&&e.total===r.RUNNING}function a(e){return e===r.FAILURE||"object"==typeof e&&e.total===r.FAILURE}function i(e){return e===r.SUCCESS||"object"==typeof e&&e.total===r.SUCCESS}t.ParallelBackground=o},"./src/decorators/CanActivateAction.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.CanActivateAction=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts");class n extends r.Decorator{constructor(){super(...arguments),this.nodeType="CanActivateActionDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}condition(e){return!!o.AI.CanActivateAction(this.config.action)===this.config.isSet}}t.CanActivateAction=(e,t,s=!0,o=r.ObserverAborts.None)=>new n({node:e,config:{action:t,isSet:s,observerAborts:o}})},"./src/decorators/ForceSuccess.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.ForceSuccess=void 0;const r=s("./node_modules/behaviortree/lib/index.js");class o extends r.Decorator{constructor(){super(...arguments),this.nodeType="ForceSuccessDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}decorate(e,t,s){return(o=super.decorate(e,t,s))===r.RUNNING||"object"==typeof o&&o.total===r.RUNNING?r.RUNNING:r.SUCCESS;var o}}t.ForceSuccess=(e,t=r.ObserverAborts.None)=>new o({node:e,config:{start:e.blueprint.start,observerAborts:t}})},"./src/decorators/IsSet.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.IsSet=void 0;const r=s("./node_modules/behaviortree/lib/index.js");class o extends r.Decorator{constructor(){super(...arguments),this.nodeType="IsSetDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}condition(e){return!!e[this.config.blackboardKey]===this.config.isSet}}t.IsSet=(e,t,s=!0,n=r.ObserverAborts.None)=>new o({node:e,start:e.blueprint.start,config:{blackboardKey:t,isSet:s,observerAborts:n}})},"./src/decorators/Predicate.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.Predicate=void 0;const r=s("./node_modules/behaviortree/lib/index.js");class o extends r.Decorator{constructor(){super(...arguments),this.nodeType="PredicateDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}condition(e){return this.config.predicate(e)===this.config.isSet}}t.Predicate=(e,t,s=!0,n=r.ObserverAborts.None)=>new o({node:e,config:{predicate:t,start:e.blueprint.start,isSet:s,observerAborts:n}})},"./src/helper.ts":(e,t)=>{"use strict";function s(e,t){const{X:s,Y:r,Z:o}=e,{X:n,Y:a,Z:i}=t,c={X:n-s,Y:a-r,Z:i-o};return Math.sqrt(Math.pow(c.X,2)+Math.pow(c.Y,2)+Math.pow(c.Z,2))}function r(e,t){Math.abs(t);const s=e/t;return e-t*Math.trunc(s)}Object.defineProperty(t,"__esModule",{value:!0}),t.getForwardVector=t.fmod=t.rotateZ=t.multiply=t.add=t.distanceToVec=t.distanceTo=t.isDead=void 0,t.isDead=function(e){return e.health<=0},t.distanceTo=function(e,t){return s(e.location,t.location)},t.distanceToVec=s,t.add=function(e,t){const{X:s,Y:r,Z:o}=e,{X:n,Y:a,Z:i}=t;return{X:s+n,Y:r+a,Z:o+i}},t.multiply=function(e,t){const{X:s,Y:r,Z:o}=e;return{X:s*t,Y:r*t,Z:o*t}},t.rotateZ=function(e,t){const s=t*(Math.PI/180),{X:r,Y:o,Z:n}=e;return{X:r*Math.cos(s)-o*Math.sin(s),Y:r*Math.sin(s)+o*Math.cos(s),Z:n}},t.fmod=r,t.getForwardVector=function(e){const{X:t,Y:s,Z:o}=e,n=e=>e*(Math.PI/180),a=r(s,360),i=r(o,360),c=Math.sin(n(a)),l=Math.cos(n(a)),u=Math.sin(n(i));return{X:l*Math.cos(n(i)),Y:l*u,Z:c}}},"./src/index.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.AI=void 0;const r=s("./src/mech.ts");t.AI=Context.GetOwner(),Context.OnMessage=(e,t)=>{try{switch(e){case"onTick":(0,r.onTick)(JSON.parse(t));break;case"onBegin":(0,r.onBegin)(JSON.parse(t))}}catch(e){console.log(e)}}},"./src/mech.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.clearBlackboardTarget=t.onTick=t.onBegin=t.tree=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/helper.ts"),n=s("./src/index.ts"),a=s("./src/trees/BT_Root.ts"),i=s("./src/utils.ts");function c(){const e=t.tree.blackboard;e.target=null,e.canSeeTarget=!1,void 0!==e.targetLastKnownLocation&&(delete e.targetLastKnownLocation,delete e.targetPredictedLocation)}function l(e){const s=t.tree.blackboard,r=[e=>1-(e.health+e.shield)/(e.healthMax+e.shieldMax),e=>1-Math.min(1,(0,o.distanceTo)(s.input.self,e)/5e4)];return r.map((t=>t(e))).reduce(((e,t)=>e+t))/r.length}t.tree=new r.BehaviorTree({tree:a.BT_Root,blackboard:{target:null,eqsResults:{}}}),t.onBegin=e=>{const s=t.tree.blackboard;for(let t of e.self.weapons)if(void 0!==t.tags.find((e=>"Weapon.Secondary"===e))){s.secondaryWeapon=t,s.canUseSpecialAttack=!0;break}for(let t of e.self.weapons)if(void 0!==t.tags.find((e=>"Weapon.Melee"===e))){s.canMelee=!0;break}console.log(`${e.self.name} AI Started`)},t.onTick=e=>{const s=t.tree.blackboard;0!==e.errors.length&&e.errors.forEach((e=>console.log(`${e.severity}: ${e.command}: ${e.message}`))),function(e){const s=t.tree.blackboard;s.input=e;const r=function(e){const s=e.input.perception.sight;if(e.input.perception.damage,0===s.length)return e.target;const r=s.filter((e=>function(e,s=!1){const r=t.tree.blackboard;return[()=>e.health>0,()=>r.input.self.factionID!==e.factionID,()=>(0,o.distanceTo)(r.input.self,e)<=5e4].map((e=>e())).reduce(((e,t)=>e&&t))}(e))),n=r.map(l),a=n.indexOf(Math.max(...n));if(-1===a){if(e.target){const t=s.findIndex((t=>t.hash===e.target.hash));return-1!==t&&s[t].health<=0?null:e.target}return null}return r[a]}(s);null===r?c():s.target=r,function(e){const s=t.tree.blackboard;if(void 0!==s.damageInstigatorHash&&-1!==e.findIndex((e=>e.hash===s.damageInstigatorHash&&e.health<=0))&&function(){const e=t.tree.blackboard;e.damageInstigatorHash=void 0,e.damageStimulusDirection=void 0,e.damageStimulusFocalPoint=void 0}(),s.target){if(0===e.length)s.canSeeTarget=!1;else{const t=e.findIndex((e=>e.hash===s.target.hash));s.canSeeTarget=-1!==t,s.canSeeTarget&&(s.targetLastKnownLocation=s.target.location,s.targetPredictedLocation=s.target.location,s.targetLastKnownVelocity=s.target.velocity)}void 0!==s.targetLastKnownLocation&&(s.targetPredictedLocation=(0,o.add)(s.targetPredictedLocation,(0,o.multiply)(s.targetLastKnownVelocity,s.input.deltaTime)))}}(e.perception.sight),function(e){if(0===e.length)return;const s=t.tree.blackboard,r=e.length-1;e[r].friendly||(s.damageInstigatorHash=e[r].instigatorHash,s.damageStimulusDirection=e[r].damageDirection,s.damageStimulusFocalPoint=(0,o.add)(s.input.self.location,(0,o.multiply)(s.damageStimulusDirection,1e4)),s.lastHitLocation=s.input.self.location,s.isLastDamageFromTarget=s.target&&s.target.hash===e[r].instigatorHash)}(e.perception.damage),function(e){if(0===e.length)return;const s=t.tree.blackboard,r=e.length-1;e[r].friendly||"Taunt"===e[r].tag&&(s.heardNoise=!0,s.noiseLocation=e[r].location)}(e.perception.sound),function(e){const s=t.tree.blackboard;if(s.interactables=e,0===s.interactables.length)s.desiredPickUpLocation=void 0;else{const e=function(e){const t=function(e){const t=e.input.self,s=e=>1-t.health/t.healthMax,r=e=>1-t.shield/t.shieldMax,n=e=>1-Math.min(1,(0,o.distanceToVec)(t.location,e.location)/5e4),a=[s,e=>r()-1,n],i=[e=>s()-1,r,n];let c=[];for(const t of e.interactables){let e=0;"Pickup.Heal"===t.tag?e=a.map((e=>e(t))).reduce(((e,t)=>e+t)):"Pickup.Shield"===t.tag?e=i.map((e=>e(t))).reduce(((e,t)=>e+t)):console.log("TODO for ammo crate"),c.push(e)}return c}(e),s=t.indexOf(Math.max(...t));return t[s]>0?e.interactables[s]:void 0}(s);void 0!==e&&(s.desiredPickUpLocation=e.location)}}(e.perception.interactable)}(e),t.tree.step();for(let[t,r]of Object.entries(e.eqs))s.eqsResults[t]=r,2===r.status&&n.AI.EQS_Complete((0,i.StringToEQSQueryType)(t))},t.clearBlackboardTarget=c},"./src/predicates/Predicate_HasLowShield.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.HasLowShield=void 0,t.HasLowShield=e=>{let t=e.input.self;return t.shield/t.shieldMax<=.3}},"./src/predicates/Predicate_HasVeryLowTotalHealth.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.HasVeryLowTotalHealth=void 0,t.HasVeryLowTotalHealth=e=>{let t=e.input.self;return(t.health+t.shield)/(t.healthMax+t.shieldMax)<=.3}},"./src/predicates/Predicate_IsOutnumbered.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.IsOutnumbered=void 0,t.IsOutnumbered=e=>{const t=e.input.self.factionID,s=e.input.perception.sight.filter((e=>e.factionID===t&&e.health>0)),r=e.input.perception.sight.filter((e=>e.factionID!==t&&e.health>0));return s.length+1<r.length}},"./src/predicates/Predicate_IsOutnumberingEnemies.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.IsOutnumberingEnemies=void 0,t.IsOutnumberingEnemies=e=>{const t=e.input.self.factionID,s=e.input.perception.sight.filter((e=>e.factionID===t&&e.health>0)),r=e.input.perception.sight.filter((e=>e.factionID!==t&&e.health>0));return s.length+1>r.length}},"./src/predicates/Predicate_TargetHasMoreTotalHealth.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.TargetHasMoreTotalHealth=void 0,t.TargetHasMoreTotalHealth=e=>{const t=e.input.self,s=e.target;if(null===s)return!1;const r=t.health+t.shield;return s.health+s.shield>r}},"./src/tasks/BTT_ClearTarget.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_ClearTarget=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/mech.ts");t.BTT_ClearTarget=new r.Task({run:e=>((0,o.clearBlackboardTarget)(),r.SUCCESS)})},"./src/tasks/BTT_EQSSetArgument.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_EQSSetArgumentVector=t.BTT_EQSSetArgumentString=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts");t.BTT_EQSSetArgumentString=(e,t,s)=>new r.Task({run:n=>{const a=s(n);return o.AI.EQS_SetArgumentString(e,t,a),r.SUCCESS}}),t.BTT_EQSSetArgumentVector=(e,t,s)=>new r.Task({run:n=>{const a=s(n);return o.AI.EQS_SetArgumentVector(e,t,a),r.SUCCESS}})},"./src/tasks/BTT_LookAt.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_LookAt=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts"),n=s("./src/utils.ts");t.BTT_LookAt=e=>new r.Task({start:t=>{const s=t[e];if(s&&(0,n.IsVector)(s))return o.AI.LookAt(s),r.SUCCESS},run:e=>{switch(o.AI.QueryStatus("Action.LookAt")){case 0:return r.RUNNING;case 2:default:return r.FAILURE;case 1:return r.SUCCESS}}})},"./src/tasks/BTT_MeleeAttack.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_MeleeAttack=void 0;const r=s("./src/index.ts"),o=s("./node_modules/behaviortree/lib/index.js");t.BTT_MeleeAttack=e=>new o.Task({run:()=>(r.AI.WeaponTrigger(e),o.RUNNING),end:()=>{r.AI.WeaponRelease(e)},abort:()=>{r.AI.WeaponRelease(e)}})},"./src/tasks/BTT_MoveTo.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_MoveTo=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts"),n=s("./src/utils.ts");t.BTT_MoveTo=(e,t=!1,s=800,a=20)=>new r.Task({start:t=>{const a=t[e];return a&&(0,n.IsVector)(a)&&o.AI.MoveToVector(a,s)?r.SUCCESS:r.FAILURE},run:a=>{if(t){const t=a[e];if(!t||!(0,n.IsVector)(t))return r.FAILURE;if(!o.AI.MoveToVector(t,s))return r.FAILURE}switch(o.AI.QueryMovementResult()){case 0:return r.RUNNING;case 1:return r.SUCCESS;default:return r.FAILURE}}})},"./src/tasks/BTT_RunEQSQuery.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_RunEQSQuery=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts");t.BTT_RunEQSQuery=(e,t)=>new r.Task({start:t=>(t.eqsResults[e]={status:1},o.AI.EQS_Query(e),r.SUCCESS),run:s=>{const o=s.eqsResults[e];if(!o)return r.FAILURE;switch(o.status){case 1:return r.RUNNING;case 3:default:return r.FAILURE;case 2:return s[t]=s.eqsResults[e].location,r.SUCCESS}}})},"./src/tasks/BTT_SetValue.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SetValue=void 0;const r=s("./node_modules/behaviortree/lib/index.js");t.BTT_SetValue=e=>new r.Task({run:t=>(e(t),r.SUCCESS)})},"./src/tasks/BTT_Shoot.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Shoot=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts");t.BTT_Shoot=e=>new r.Task({run:t=>{if(-1===t.input.self.weapons.findIndex((t=>t.tags.findIndex((t=>t===e)))))return r.FAILURE;const s=o.AI.WeaponGetAmmoByTag(e)>0;return s?o.AI.WeaponTrigger(e,t.targetLastKnownLocation):o.AI.WeaponRelease(e),s?r.RUNNING:r.FAILURE},end:()=>{o.AI.WeaponRelease(e)},abort:()=>{o.AI.WeaponRelease(e)}})},"./src/tasks/BTT_SpecialAttack.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SpecialAttack=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts"),n=s("./src/utils.ts");t.BTT_SpecialAttack=e=>new r.Task({start:t=>{const s=t[e];return s&&(0,n.IsVector)(s)?void 0===t.secondaryWeapon||null===t.secondaryWeapon?r.FAILURE:o.AI.TrySpecialAttack(s)?r.SUCCESS:r.FAILURE:r.FAILURE},run:e=>{switch(o.AI.QueryStatus("Action.SpecialAttack")){case 0:return r.RUNNING;case 2:default:return r.FAILURE;case 1:return r.SUCCESS}}})},"./src/tasks/BTT_StopMoveTo.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_StopMoveTo=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts");t.BTT_StopMoveTo=()=>new r.Task({run:()=>(o.AI.StopMoveTo(),r.SUCCESS)})},"./src/tasks/BTT_Success.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Success=void 0;const r=s("./node_modules/behaviortree/lib/index.js");t.BTT_Success=new r.Task({run:e=>r.SUCCESS})},"./src/tasks/BTT_Taunt.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Taunt=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts");t.BTT_Taunt=new r.Task({start:e=>o.AI.Taunt()?r.SUCCESS:r.FAILURE,run:e=>{switch(o.AI.QueryStatus("Action.Taunt")){case 0:return r.RUNNING;case 2:default:return r.FAILURE;case 1:return r.SUCCESS}}})},"./src/tasks/BTT_Wait.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Wait=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts");t.BTT_Wait=e=>new r.Task({start:t=>o.AI.Wait(e)?r.SUCCESS:r.FAILURE,run:e=>{switch(o.AI.QueryStatus("Action.Wait")){case 0:return r.RUNNING;case 2:default:return r.FAILURE;case 1:return r.SUCCESS}}})},"./src/tasks/focus/BTT_SetFocalPoint.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SetFocalPoint=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/index.ts"),n=s("./src/utils.ts");t.BTT_SetFocalPoint=e=>new r.Task({start:t=>{const s=t[e];return s?(0,n.IsWarMachine)(s)?o.AI.SetFocalPointByHash(s.hash)?r.SUCCESS:r.FAILURE:(0,n.IsVector)(s)?o.AI.SetFocalPointByLocation(s)?r.SUCCESS:r.FAILURE:(console.log("BTT_SetFocalPoint: Invalid focal point type."),r.FAILURE):r.FAILURE},run:e=>r.SUCCESS})},"./src/trees/BT_Camp.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Camp=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/trees/BT_GetCover.ts"),n=s("./src/branches/ParallelBackground.ts"),a=s("./src/decorators/IsSet.ts"),i=s("./src/tasks/BTT_MoveTo.ts"),c=s("./src/trees/BT_LookAround.ts"),l=s("./src/trees/BT_SetFocal.ts"),u=s("./src/tasks/BTT_SetValue.ts");t.BT_Camp=new r.Sequence({nodes:[new n.ParallelBackground({nodes:[new r.Sequence({nodes:[new r.Selector({nodes:[(0,a.IsSet)(o.BT_GetCover,"coverLocation",!1),(0,a.IsSet)((0,i.BTT_MoveTo)("coverLocation"),"coverLocation")]}),(0,u.BTT_SetValue)((e=>e.coverLocation=void 0))]}),l.BT_SetFocal]}),c.BT_LookAround]})},"./src/trees/BT_GetCover.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_GetCover=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/tasks/BTT_EQSSetArgument.ts"),n=s("./src/tasks/BTT_MoveTo.ts"),a=s("./src/tasks/BTT_RunEQSQuery.ts"),i=s("./src/tasks/BTT_SetValue.ts");t.BT_GetCover=new r.Sequence({nodes:[(0,o.BTT_EQSSetArgumentVector)("cover","TargetLastKnownLocation",(e=>void 0!==e.targetLastKnownLocation?e.targetLastKnownLocation:e.input.self.location)),(0,o.BTT_EQSSetArgumentVector)("cover","LastHitLocation",(e=>void 0!==e.lastHitLocation?e.lastHitLocation:e.input.self.location)),(0,a.BTT_RunEQSQuery)("cover","coverLocation"),(0,n.BTT_MoveTo)("coverLocation"),(0,i.BTT_SetValue)((e=>e.coverLocation=void 0))]})},"./src/trees/BT_GetPickup.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_GetPickup=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/branches/ParallelBackground.ts"),n=s("./src/tasks/BTT_MoveTo.ts"),a=s("./src/tasks/BTT_SetValue.ts"),i=s("./src/tasks/BTT_Success.ts"),c=s("./src/trees/BT_SetFocal.ts");t.BT_GetPickup=new o.ParallelBackground({nodes:[new r.Sequence({nodes:[new r.Selector({nodes:[(0,n.BTT_MoveTo)("desiredPickUpLocation",!0),i.BTT_Success]}),(0,a.BTT_SetValue)((e=>e.desiredPickUpLocation=void 0))]}),c.BT_SetFocal]})},"./src/trees/BT_InvestigateNoise.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_InvestigateNoise=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/decorators/ForceSuccess.ts"),n=s("./src/tasks/BTT_EQSSetArgument.ts"),a=s("./src/tasks/BTT_MoveTo.ts"),i=s("./src/tasks/BTT_RunEQSQuery.ts"),c=s("./src/tasks/BTT_SetValue.ts"),l=s("./src/tasks/focus/BTT_SetFocalPoint.ts");t.BT_InvestigateNoise=new r.Sequence({nodes:[(0,l.BTT_SetFocalPoint)("noiseLocation"),(0,o.ForceSuccess)((0,a.BTT_MoveTo)("noiseLocation")),(0,n.BTT_EQSSetArgumentVector)("hidden","TargetPredictedLocation",(e=>e.noiseLocation)),(0,c.BTT_SetValue)((e=>e.noiseLocation=void 0)),(0,c.BTT_SetValue)((e=>e.heardNoise=!1)),(0,i.BTT_RunEQSQuery)("hidden","hiddenLocation"),(0,l.BTT_SetFocalPoint)("hiddenLocation"),(0,a.BTT_MoveTo)("hiddenLocation"),(0,c.BTT_SetValue)((e=>e.hiddenLocation=void 0))]})},"./src/trees/BT_LookAround.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_LookAround=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/helper.ts"),n=s("./src/tasks/BTT_LookAt.ts"),a=s("./src/tasks/BTT_SetValue.ts"),i=s("./src/tasks/BTT_Wait.ts");t.BT_LookAround=new r.Sequence({nodes:[(0,a.BTT_SetValue)((e=>e.lookAtLocation=(0,o.add)(e.input.self.location,(0,o.multiply)((0,o.rotateZ)((0,o.getForwardVector)(e.input.self.rotation),90),1e3)))),(0,n.BTT_LookAt)("lookAtLocation"),(0,i.BTT_Wait)(1),(0,a.BTT_SetValue)((e=>e.lookAtLocation=(0,o.add)(e.input.self.location,(0,o.multiply)((0,o.rotateZ)((0,o.getForwardVector)(e.input.self.rotation),90),1e3)))),(0,n.BTT_LookAt)("lookAtLocation"),(0,i.BTT_Wait)(1),(0,a.BTT_SetValue)((e=>e.lookAtLocation=void 0))]})},"./src/trees/BT_Patrol.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Patrol=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/tasks/BTT_MoveTo.ts"),n=s("./src/tasks/BTT_RunEQSQuery.ts"),a=s("./src/tasks/BTT_SetValue.ts"),i=s("./src/tasks/focus/BTT_SetFocalPoint.ts");t.BT_Patrol=new r.Sequence({nodes:[(0,n.BTT_RunEQSQuery)("patrol","patrolLocation"),(0,i.BTT_SetFocalPoint)("patrolLocation"),(0,o.BTT_MoveTo)("patrolLocation"),(0,a.BTT_SetValue)((e=>e.patrolLocation=void 0))]})},"./src/trees/BT_ReceivedDamage.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_ReceivedDamage=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/helper.ts"),n=s("./src/tasks/BTT_EQSSetArgument.ts"),a=s("./src/tasks/BTT_LookAt.ts"),i=s("./src/tasks/BTT_MoveTo.ts"),c=s("./src/tasks/BTT_RunEQSQuery.ts"),l=s("./src/tasks/BTT_SetValue.ts"),u=s("./src/tasks/BTT_StopMoveTo.ts"),d=s("./src/tasks/focus/BTT_SetFocalPoint.ts");t.BT_ReceivedDamage=new r.Sequence({nodes:[(0,u.BTT_StopMoveTo)(),(0,a.BTT_LookAt)("damageStimulusFocalPoint"),(0,l.BTT_SetValue)((e=>e.damageStimulusFocalPoint=void 0)),(0,n.BTT_EQSSetArgumentVector)("hidden","TargetPredictedLocation",(e=>(0,o.add)(e.input.self.location,(0,o.multiply)(e.damageStimulusDirection,1e4)))),(0,c.BTT_RunEQSQuery)("hidden","hiddenLocation"),(0,d.BTT_SetFocalPoint)("hiddenLocation"),(0,i.BTT_MoveTo)("hiddenLocation"),(0,l.BTT_SetValue)((e=>e.hiddenLocation=void 0))]})},"./src/trees/BT_Root.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Root=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/decorators/CanActivateAction.ts"),n=s("./src/decorators/IsSet.ts"),a=s("./src/decorators/Predicate.ts"),i=s("./src/predicates/Predicate_HasLowShield.ts"),c=s("./src/tasks/BTT_Taunt.ts"),l=s("./src/tasks/BTT_Wait.ts"),u=s("./src/trees/BT_Camp.ts"),d=s("./src/trees/combat/BT_Combat.ts"),T=s("./src/trees/BT_GetPickup.ts"),h=s("./src/trees/BT_InvestigateNoise.ts"),_=s("./src/trees/BT_Patrol.ts"),p=s("./src/trees/BT_ReceivedDamage.ts");t.BT_Root=new r.Selector({nodes:[(0,n.IsSet)(d.BT_Combat,"target",!0,r.ObserverAborts.Both),(0,n.IsSet)(T.BT_GetPickup,"desiredPickUpLocation",!0,r.ObserverAborts.Both),(0,a.Predicate)(u.BT_Camp,i.HasLowShield,!0,r.ObserverAborts.LowerPriority),(0,o.CanActivateAction)(c.BTT_Taunt,"Action.Taunt",!0),(0,n.IsSet)(p.BT_ReceivedDamage,"damageStimulusFocalPoint",!0,r.ObserverAborts.LowerPriority),(0,n.IsSet)(h.BT_InvestigateNoise,"heardNoise",!0,r.ObserverAborts.LowerPriority),_.BT_Patrol,(0,l.BTT_Wait)(1)]})},"./src/trees/BT_SearchTarget.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_SearchTarget=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/branches/ParallelBackground.ts"),n=s("./src/decorators/IsSet.ts"),a=s("./src/tasks/BTT_ClearTarget.ts"),i=s("./src/tasks/BTT_EQSSetArgument.ts"),c=s("./src/tasks/BTT_MoveTo.ts"),l=s("./src/tasks/BTT_RunEQSQuery.ts"),u=s("./src/trees/BT_SetFocal.ts");t.BT_SearchTarget=new r.Sequence({nodes:[new o.ParallelBackground({nodes:[new r.Sequence({nodes:[(0,n.IsSet)((0,c.BTT_MoveTo)("targetLastKnownLocation"),"targetLastKnownLocation"),(0,n.IsSet)(new r.Sequence({nodes:[(0,i.BTT_EQSSetArgumentVector)("hidden","TargetPredictedLocation",(e=>e.targetPredictedLocation)),(0,l.BTT_RunEQSQuery)("hidden","hiddenLocation"),(0,c.BTT_MoveTo)("hiddenLocation")]}),"targetPredictedLocation")]}),u.BT_SetFocal]}),a.BTT_ClearTarget]})},"./src/trees/BT_SetFocal.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_SetFocal=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/decorators/IsSet.ts"),n=s("./src/tasks/BTT_Success.ts"),a=s("./src/tasks/focus/BTT_SetFocalPoint.ts");t.BT_SetFocal=new r.Selector({nodes:[(0,o.IsSet)((0,a.BTT_SetFocalPoint)("target"),"canSeeTarget",!0,r.ObserverAborts.LowerPriority),(0,o.IsSet)((0,a.BTT_SetFocalPoint)("damageStimulusFocalPoint"),"damageStimulusFocalPoint",!0,r.ObserverAborts.LowerPriority),(0,o.IsSet)((0,a.BTT_SetFocalPoint)("targetPredictedLocation"),"targetPredictedLocation",!0,r.ObserverAborts.LowerPriority),(0,o.IsSet)((0,a.BTT_SetFocalPoint)("targetLastKnownLocation"),"targetLastKnownLocation",!0,r.ObserverAborts.LowerPriority),n.BTT_Success]})},"./src/trees/BT_Strafe.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Strafe=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/tasks/BTT_EQSSetArgument.ts"),n=s("./src/tasks/BTT_MoveTo.ts"),a=s("./src/tasks/BTT_RunEQSQuery.ts"),i=s("./src/tasks/BTT_SetValue.ts");t.BT_Strafe=new r.Sequence({nodes:[(0,o.BTT_EQSSetArgumentString)("strafe","TargetHash",(e=>e.target.hash)),(0,a.BTT_RunEQSQuery)("strafe","strafeLocation"),(0,n.BTT_MoveTo)("strafeLocation"),(0,i.BTT_SetValue)((e=>e.strafeLocation=void 0))]})},"./src/trees/combat/BT_CanSeeTarget.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_CanSeeTarget=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/decorators/CanActivateAction.ts"),n=s("./src/decorators/Predicate.ts"),a=s("./src/helper.ts"),i=s("./src/tasks/BTT_SpecialAttack.ts"),c=s("./src/trees/combat/BT_CloseCombat.ts"),l=s("./src/trees/combat/BT_RangeCombat.ts");t.BT_CanSeeTarget=new r.Selector({nodes:[(0,o.CanActivateAction)((0,i.BTT_SpecialAttack)("targetLastKnownLocation"),"Action.SpecialAttack",!0,r.ObserverAborts.LowerPriority),(0,n.Predicate)(c.BT_CloseCombat,(e=>e.canMelee&&void 0!==e.targetLastKnownLocation&&(0,a.distanceToVec)(e.input.self.location,e.targetLastKnownLocation)<=4e3),!0,r.ObserverAborts.Both),l.BT_RangeCombat]})},"./src/trees/combat/BT_CloseCombat.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_CloseCombat=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/branches/ParallelBackground.ts"),n=s("./src/decorators/IsSet.ts"),a=s("./src/decorators/Predicate.ts"),i=s("./src/predicates/Predicate_HasVeryLowTotalHealth.ts"),c=s("./src/tasks/BTT_MeleeAttack.ts"),l=s("./src/tasks/BTT_MoveTo.ts"),u=s("./src/tasks/BTT_Success.ts"),d=s("./src/trees/BT_GetCover.ts"),T=s("./src/trees/BT_GetPickup.ts"),h=s("./src/trees/BT_SetFocal.ts");t.BT_CloseCombat=new o.ParallelBackground({nodes:[(0,c.BTT_MeleeAttack)("Weapon.Melee"),h.BT_SetFocal,new r.Selector({nodes:[(0,n.IsSet)(T.BT_GetPickup,"desiredPickUpLocation",!0,r.ObserverAborts.Both),(0,a.Predicate)(d.BT_GetCover,i.HasVeryLowTotalHealth,!0,r.ObserverAborts.LowerPriority),(0,l.BTT_MoveTo)("targetLastKnownLocation",!0),u.BTT_Success]})]})},"./src/trees/combat/BT_Combat.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Combat=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/decorators/IsSet.ts"),n=s("./src/decorators/Predicate.ts"),a=s("./src/predicates/Predicate_HasLowShield.ts"),i=s("./src/trees/BT_Camp.ts"),c=s("./src/trees/combat/BT_CanSeeTarget.ts"),l=s("./src/trees/BT_GetPickup.ts"),u=s("./src/trees/BT_SearchTarget.ts");t.BT_Combat=new r.Selector({nodes:[(0,o.IsSet)(c.BT_CanSeeTarget,"canSeeTarget",!0,r.ObserverAborts.Both),(0,o.IsSet)(l.BT_GetPickup,"desiredPickUpLocation",!0,r.ObserverAborts.Both),(0,n.Predicate)(i.BT_Camp,a.HasLowShield,!0,r.ObserverAborts.LowerPriority),(0,n.Predicate)(u.BT_SearchTarget,(e=>!e.canSeeTarget))]})},"./src/trees/combat/BT_RangeCombat.ts":(e,t,s)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_RangeCombat=void 0;const r=s("./node_modules/behaviortree/lib/index.js"),o=s("./src/branches/ParallelBackground.ts"),n=s("./src/decorators/IsSet.ts"),a=s("./src/decorators/Predicate.ts"),i=s("./src/predicates/Predicate_HasVeryLowTotalHealth.ts"),c=s("./src/predicates/Predicate_IsOutnumbered.ts"),l=s("./src/predicates/Predicate_IsOutnumberingEnemies.ts"),u=s("./src/predicates/Predicate_TargetHasMoreTotalHealth.ts"),d=s("./src/tasks/BTT_MoveTo.ts"),T=s("./src/tasks/BTT_Shoot.ts"),h=s("./src/tasks/BTT_Success.ts"),_=s("./src/trees/BT_GetCover.ts"),p=s("./src/trees/BT_GetPickup.ts"),S=s("./src/trees/BT_SetFocal.ts"),b=s("./src/trees/BT_Strafe.ts");t.BT_RangeCombat=new o.ParallelBackground({nodes:[new r.Parallel({nodes:[(0,T.BTT_Shoot)("Weapon.Primary.LeftArm"),(0,T.BTT_Shoot)("Weapon.Primary.RightArm")]}),S.BT_SetFocal,new r.Selector({nodes:[(0,n.IsSet)(p.BT_GetPickup,"desiredPickUpLocation",!0,r.ObserverAborts.Both),(0,a.Predicate)(_.BT_GetCover,i.HasVeryLowTotalHealth,!0,r.ObserverAborts.LowerPriority),(0,a.Predicate)((0,d.BTT_MoveTo)("targetLastKnownLocation"),(e=>!(0,u.TargetHasMoreTotalHealth)(e)&&!(0,c.IsOutnumbered)(e)||(0,l.IsOutnumberingEnemies)(e)),!0,r.ObserverAborts.Both),b.BT_Strafe,h.BTT_Success]})]})},"./src/utils.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.IsWarMachine=t.IsVector=t.StringToEQSQueryType=void 0,t.StringToEQSQueryType=e=>{switch(e){case"away":return"away";case"cover":return"cover";case"hidden":return"hidden";case"patrol":return"patrol";case"strafe":return"strafe"}},t.IsVector=e=>"X"in e&&"Y"in e,t.IsWarMachine=e=>"hash"in e}},t={};!function s(r){var o=t[r];if(void 0!==o)return o.exports;var n=t[r]={exports:{}};return e[r](n,n.exports,s),n.exports}("./src/mech.ts")})();
//# sourceMappingURL=mech.js.map