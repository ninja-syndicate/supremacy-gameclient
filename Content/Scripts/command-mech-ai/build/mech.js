/*! For license information please see mech.js.LICENSE.txt */
(()=>{var e={"./node_modules/behaviortree/lib/index.js":e=>{var t,r=Object.defineProperty,o=Object.defineProperties,s=Object.getOwnPropertyDescriptor,n=Object.getOwnPropertyDescriptors,a=Object.getOwnPropertyNames,i=Object.getOwnPropertySymbols,c=Object.prototype.hasOwnProperty,l=Object.prototype.propertyIsEnumerable,u=(e,t,o)=>t in e?r(e,t,{enumerable:!0,configurable:!0,writable:!0,value:o}):e[t]=o,d=(e,t)=>{for(var r in t||(t={}))c.call(t,r)&&u(e,r,t[r]);if(i)for(var r of i(t))l.call(t,r)&&u(e,r,t[r]);return e},T=(e,t)=>o(e,n(t)),h=(e,t)=>{var r={};for(var o in e)c.call(e,o)&&t.indexOf(o)<0&&(r[o]=e[o]);if(null!=e&&i)for(var o of i(e))t.indexOf(o)<0&&l.call(e,o)&&(r[o]=e[o]);return r},p=(e,t)=>{for(var o in t)r(e,o,{get:t[o],enumerable:!0})},m=(t="undefined"!=typeof WeakMap?new WeakMap:0,(e,o)=>t&&t.get(e)||(o=((e,t,o,n)=>{if(t&&"object"==typeof t||"function"==typeof t)for(let o of a(t))!c.call(e,o)&&r(e,o,{get:()=>t[o],enumerable:!(n=s(t,o))||n.enumerable});return e})(r({},"__esModule",{value:!0}),e),t&&t.set(e,o),o)),b={};p(b,{BehaviorTree:()=>R,BehaviorTreeImporter:()=>G,BranchNode:()=>Q,Decorator:()=>O,FAILURE:()=>_,Introspector:()=>X,Node:()=>k,ObserverAborts:()=>U,Parallel:()=>Y,ParallelComplete:()=>H,ParallelSelector:()=>K,RUNNING:()=>g,Random:()=>V,SUCCESS:()=>S,Selector:()=>W,Sequence:()=>Z,Task:()=>C,decorators:()=>M,default:()=>q,getRegistry:()=>A,registryLookUp:()=>I});var g=Symbol("running"),S=!0,_=!1;function f(e){return e===g||"object"==typeof e&&e.total===g}var v=()=>!1,B=()=>!0,y=()=>{},P=()=>{},k=class{constructor(e){this.nodeType="Node",this.ranStart=!1;var t=e,{run:r=v,start:o=B,end:s=y,abort:n=P}=t,a=h(t,["run","start","end","abort"]);this.blueprint=d({run:r,start:o,end:s,abort:n},a)}run(e,t={}){var r=t,{introspector:o,rerun:s=!1,registryLookUp:n=(e=>e)}=r,a=h(r,["introspector","rerun","registryLookUp"]);if(!s||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===_)return t}let i=this.blueprint.run(e,T(d({},a),{rerun:s,registryLookUp:n}));return i!==g&&this.blueprint.end(e),o&&o.push(this,i,e),i}abort(e,{registryLookUp:t=(e=>e),lastRun:r}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:r})}get name(){return this._name||this.blueprint.name}set name(e){this._name=e}},C=class extends k{constructor(){super(...arguments),this.nodeType="Task"}},L={};function A(){return L}function I(e){if("string"==typeof e){let t=L[e];if(!t)throw new Error(`No node with name ${e} registered.`);return t}return e}var R=class{constructor({tree:e,blackboard:t}){this.tree=e,this.blackboard=t,this.lastResult=void 0}step({introspector:e}={}){let t=this.lastResult&&"object"==typeof this.lastResult?this.lastResult:void 0,r=f(this.lastResult);e&&e.start(this),this.lastResult=I(this.tree).run(this.blackboard,{lastRun:t,introspector:e,rerun:r,registryLookUp:I}),e&&e.end()}static register(e,t){L[e]="function"==typeof t?new C({name:e,run:t}):t}static cleanRegistry(){L={}}},M={};p(M,{AlwaysFailDecorator:()=>F,AlwaysSucceedDecorator:()=>j,CooldownDecorator:()=>E,InvertDecorator:()=>N,LoopDecorator:()=>D});var w,U=((w=U||{})[w.None=0]="None",w[w.Self=1]="Self",w[w.LowerPriority=2]="LowerPriority",w[w.Both=3]="Both",w),x=e=>"observerAborts"in e,O=class extends k{constructor(e={config:{}}){var t=e,{config:r={}}=t;super(h(t,["config"])),this.nodeType="Decorator",this.observerAborts=0,this.setConfig(r)}condition(e){return S}decorate(e,t,r,o){return this.condition(t)||o&&1!==this.observerAborts&&3!==this.observerAborts?e(e,t,r):_}run(e,t={}){var r=t,{introspector:o,rerun:s,registryLookUp:n=(e=>e)}=r,a=h(r,["introspector","rerun","registryLookUp"]);if(!s||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===_)return t}let i=0,c=this.decorate((()=>(++i,n(this.blueprint.node).run(e,T(d({},a),{rerun:s,introspector:o,registryLookUp:n})))),e,this.config,s);return c!==g&&(this.blueprint.end(e),void 0!==(c===_&&this.blueprint.node)&&this.blueprint.node.blueprint.end(e)),o&&o.wrapLast(i,this,c,e),c}abort(e,{registryLookUp:t=(e=>e),lastRun:r}={}){super.abort(e,{registryLookUp:t,lastRun:r}),void 0!==this.blueprint.node&&this.blueprint.node.abort(e,{registryLookUp:t,lastRun:r})}setConfig(e){this.config=e}},F=class extends O{constructor(){super(...arguments),this.nodeType="AlwaysFailDecorator"}decorate(e){let t=e();return f(t)?t:_}},j=class extends O{constructor(){super(...arguments),this.nodeType="AlwaysSucceedDecorator"}decorate(e){let t=e();return f(t)?t:S}},E=class extends O{constructor(){super(...arguments),this.lock=!1,this.nodeType="CooldownDecorator"}setConfig({cooldown:e=5}){this.config={cooldown:e}}decorate(e){if(this.lock)return _;let t=e();return f(t)||(this.lock=!0,setTimeout((()=>{this.lock=!1}),1e3*this.config.cooldown)),t}},N=class extends O{constructor(){super(...arguments),this.nodeType="InvertDecorator"}decorate(e){let t=e();return f(t)?t:t===S?_:S}},D=class extends O{constructor(){super(...arguments),this.nodeType="LoopDecorator"}setConfig({loop:e=1/0}){this.config={loop:e}}decorate(e){let t=0,r=_;for(;t++<this.config.loop;)if(r=e(),r===_)return _;return r}},Q=class extends k{constructor(e){super(e),this.OPT_OUT_CASE=S,this.START_CASE=S,this.nodeType="BranchNode",this.nodes=e.nodes||[],this.numNodes=this.nodes.length,this.observedDecorators=new Map}run(e={},{lastRun:t,introspector:r,rerun:o,registryLookUp:s=(e=>e)}={}){if(!o||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===_)return t}let n=this.START_CASE,a=[],i="object"==typeof t&&t.state||[],c=Math.max(i.findIndex((e=>f(e))),0),l=0;for(;l<this.numNodes;++l){let t=!1;if(o&&this.observedDecorators.has(l))t=!0;else if(l<c){a[l]=i[l];continue}let u=s(this.nodes[l]);if(t&&x(u))if(this.observedDecorators.get(l)===u.condition(e)){if(o&&l<c){a[l]=i[l];continue}}else s(this.nodes[c]).abort(e,{registryLookUp:s,lastRun:i[c]}),c=0;let d=u.run(e,{lastRun:i[l],introspector:r,rerun:o,registryLookUp:s});if(a[l]=d,x(u)&&u.observerAborts>0&&this.observedDecorators.set(l,u.condition(e)),d===g||"object"==typeof d){n=g;break}if(d===this.OPT_OUT_CASE){n=d;break}o=!1}let u=f(n);if(u||this.blueprint.end(e),r){let t=u?g:n;r.wrapLast(Math.min(l+1,this.numNodes),this,t,e)}return n===g?{total:n,state:a}:n}abort(e={},{lastRun:t,registryLookUp:r=(e=>e)}={}){super.abort(e,{registryLookUp:r,lastRun:t});let o="object"==typeof t&&t.state||[],s=Math.max(o.findIndex((e=>f(e))),0);r(this.nodes[s]).abort(e,{registryLookUp:r,lastRun:o[s]})}},V=class extends Q{constructor(){super(...arguments),this.nodeType="Random"}run(e={},{lastRun:t,introspector:r,rerun:o,registryLookUp:s=(e=>e)}={}){let n=0;o?n=t.state.findIndex((e=>f(e))):(this.blueprint.start(e),n=Math.floor(Math.random()*this.numNodes));let a=s(this.nodes[n]).run(e,{lastRun:t,introspector:r,rerun:o,registryLookUp:s}),i=f(a);if(i||this.blueprint.end(e),r){let t=i?g:a;r.wrapLast(1,this,t,e)}if(i){let e={total:g,state:new Array(this.numNodes).fill(void 0)};return e.state[n]=a,e}return a}},W=class extends Q{constructor(){super(...arguments),this.nodeType="Selector",this.START_CASE=_,this.OPT_OUT_CASE=S}},Z=class extends Q{constructor(){super(...arguments),this.nodeType="Sequence",this.START_CASE=S,this.OPT_OUT_CASE=_}},G=class{constructor(){this.types={task:C,decorator:O,selector:W,sequence:Z,random:V,invert:N,fail:F,succeed:j,cooldown:E,loop:D}}defineType(e,t){this.types[e]=t}parse(e){let t=e,{type:r,name:o}=t,s=h(t,["type","name"]),n=this.types[r];if(!n){let e=I(r);if(e)return e.name=o,e;throw new Error(`Don't know how to handle type ${r}. Please register this first.`)}return new n({name:o,node:e.node?this.parse(e.node):null,nodes:e.nodes?e.nodes.map((e=>this.parse(e))):null,config:s})}},X=class{constructor(){this.currentResult=[],this.results=[]}start(e){this.tree=e,this.currentResult=[]}end(){let e=this.currentResult.pop();e&&this.results.push(e),delete this.tree,this.currentResult=[]}push(e,t,r){this.currentResult.push(this._toResult(e,t,r))}wrapLast(e,t,r,o){let s=this.currentResult.splice(this.currentResult.length-e,e);this.currentResult.push(T(d({},this._toResult(t,r,o)),{children:s}))}_toResult(e,t,r){return T(d({},e.name?{name:e.name}:{}),{result:t})}reset(){this.results=[]}get lastResult(){return 0===this.results.length?null:this.results[this.results.length-1]}},Y=class extends Q{constructor(e){super(e),this.nodeType="Parallel",this.nodes=e.nodes||[],this.numNodes=this.nodes.length}run(e={},{lastRun:t,introspector:r,rerun:o,registryLookUp:s=(e=>e)}={}){if(!o||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===_)return t}let n=[];for(let a=0;a<this.numNodes;++a){let i=t&&t.state[a];if(i&&!f(i)){n[a]=i;continue}let c=s(this.nodes[a]).run(e,{lastRun:i,introspector:r,rerun:o,registryLookUp:s});n[a]=c}let a=this.calcResult(n);if(f(a)||this.blueprint.end(e),r){let t=n.find((e=>f(e)))?g:a;r.wrapLast(this.numNodes,this,t,e)}return a}calcResult(e){return e.includes(_)?_:e.find((e=>f(e)))?{total:g,state:e}:S}abort(e,{registryLookUp:t=(e=>e),lastRun:r}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:r});for(let o of this.nodes)o.abort(e,{registryLookUp:t,lastRun:r})}},H=class extends Y{constructor(){super(...arguments),this.nodeType="ParallelComplete"}calcResult(e){return e.includes(_)?_:e.includes(S)?S:{total:g,state:e}}},K=class extends Y{constructor(){super(...arguments),this.nodeType="ParallelSelector"}calcResult(e){return e.includes(_)?_:e.find((e=>f(e)))?{total:g,state:e}:S}},q=R;e.exports=m(b)},"./src/branches/ParallelBackground.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.ParallelBackground=void 0;const o=r("./node_modules/behaviortree/lib/index.js");class s extends o.Parallel{constructor(){super(...arguments),this.nodeType="ParallelBackground"}run(e={},{lastRun:t,introspector:r,rerun:s,registryLookUp:c=(e=>e)}={}){const l=[];let u=!1;if(this.ranStart)for(let r=1;r<this.numNodes;++r){let s=t&&t.state[r];if(s&&i(s)){const t=c(this.nodes[r]).blueprint.start(e);if(t===o.FAILURE){l[r]=t,u=!0;break}}}if(!s||!this.ranStart){this.ranStart=!0;const t=this.blueprint.start(e);if(t===o.FAILURE)return t}if(!u)for(let o=0;o<this.numNodes;++o){let u=t&&t.state[o];if(u&&!n(u)){if(l[o]=u,0===o)break;if(a(u))break}const d=c(this.nodes[o]),T=!i(u)&&s,h=!i(u)&&u,p=d.run(e,{lastRun:h,introspector:r,rerun:T,registryLookUp:c});if(l[o]=p,0===o&&a(p))break}const d=this.calcResult(l);if((a(d)||i(l[0]))&&this.blueprint.end(e),r){const t=l.find((e=>n(e)))?o.RUNNING:d;r.wrapLast(this.numNodes,this,t,e)}return i(l[0])?o.SUCCESS:d}abort(e,{registryLookUp:t=(e=>e),lastRun:r}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:r});for(const o of this.nodes)o.abort(e,{registryLookUp:t,lastRun:r})}calcResult(e){return e.includes(o.FAILURE)?o.FAILURE:{total:o.RUNNING,state:e}}}function n(e){return e===o.RUNNING||"object"==typeof e&&e.total===o.RUNNING}function a(e){return e===o.FAILURE||"object"==typeof e&&e.total===o.FAILURE}function i(e){return e===o.SUCCESS||"object"==typeof e&&e.total===o.SUCCESS}t.ParallelBackground=s},"./src/decorators/IsSet.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.IsSet=void 0;const o=r("./node_modules/behaviortree/lib/index.js");class s extends o.Decorator{constructor(){super(...arguments),this.nodeType="IsSetDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}condition(e){return!!e[this.config.blackboardKey]===this.config.isSet}}t.IsSet=(e,t,r=!0,n=o.ObserverAborts.None)=>new s({node:e,config:{blackboardKey:t,isSet:r,observerAborts:n}})},"./src/decorators/Predicate.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.Predicate=t.PredicateDecorator=void 0;const o=r("./node_modules/behaviortree/lib/index.js");class s extends o.Decorator{constructor(){super(...arguments),this.nodeType="PredicateDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}condition(e){return!!this.config.predicate(e)===this.config.isMatch}}t.PredicateDecorator=s,t.Predicate=(e,t,r=!0,n=o.ObserverAborts.None)=>new s({node:e,config:{predicate:t,isMatch:r,observerAborts:n}})},"./src/helper.ts":(e,t)=>{"use strict";function r(e,t){const{X:r,Y:o,Z:s}=e,{X:n,Y:a,Z:i}=t,c={X:n-r,Y:a-o,Z:i-s};return Math.sqrt(Math.pow(c.X,2)+Math.pow(c.Y,2)+Math.pow(c.Z,2))}function o(e,t){Math.abs(t);const r=e/t;return e-t*Math.trunc(r)}Object.defineProperty(t,"__esModule",{value:!0}),t.getForwardVector=t.fmod=t.rotateZ=t.multiply=t.add=t.distanceToVec=t.distanceTo=t.isDead=void 0,t.isDead=function(e){return e.health<=0},t.distanceTo=function(e,t){return r(e.location,t.location)},t.distanceToVec=r,t.add=function(e,t){const{X:r,Y:o,Z:s}=e,{X:n,Y:a,Z:i}=t;return{X:r+n,Y:o+a,Z:s+i}},t.multiply=function(e,t){const{X:r,Y:o,Z:s}=e;return{X:r*t,Y:o*t,Z:s*t}},t.rotateZ=function(e,t){const r=t*(Math.PI/180),{X:o,Y:s,Z:n}=e;return{X:o*Math.cos(r)-s*Math.sin(r),Y:o*Math.sin(r)+s*Math.cos(r),Z:n}},t.fmod=o,t.getForwardVector=function(e){const{X:t,Y:r,Z:s}=e,n=e=>e*(Math.PI/180),a=o(r,360),i=o(s,360),c=Math.sin(n(a)),l=Math.cos(n(a)),u=Math.sin(n(i));return{X:l*Math.cos(n(i)),Y:l*u,Z:c}}},"./src/index.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.AI=void 0;const o=r("./src/mech.ts");t.AI=Context.GetOwner(),Context.OnMessage=(e,t)=>{try{switch(e){case"onTick":(0,o.onTick)(JSON.parse(t));break;case"onBegin":(0,o.onBegin)(JSON.parse(t))}}catch(e){console.log(e)}}},"./src/mech.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.clearBlackboardTarget=t.onTick=t.onBegin=t.tree=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/helper.ts"),n=r("./src/index.ts"),a=r("./src/trees/BT_Root.ts"),i=r("./src/utils.ts");function c(e){const r=t.tree.blackboard,o=[e=>1-(e.health+e.shield)/(e.healthMax+e.shieldMax),e=>1-Math.min(1,(0,s.distanceTo)(r.input.self,e)/5e4)];return o.map((t=>t(e))).reduce(((e,t)=>e+t))/o.length}function l(){const e=t.tree.blackboard;e.target=null,e.canSeeTarget=!1,void 0!==e.targetLostSightTime&&delete e.targetLostSightTime,void 0!==e.targetLastKnownLocation&&delete e.targetLastKnownLocation,void 0!==e.targetPredictedLocation&&delete e.targetPredictedLocation}t.tree=new o.BehaviorTree({tree:a.BT_Root,blackboard:{target:null,eqsResults:{}}}),t.onBegin=e=>{const r=t.tree.blackboard;for(let t of e.self.weapons)if(void 0!==t.tags.find((e=>"Weapon.Secondary"===e))){r.secondaryWeapon=t,r.canUseSpecialAttack=!0;break}for(let t of e.self.weapons)if(void 0!==t.tags.find((e=>"Weapon.Melee"===e))){r.canMelee=!0;break}r.currentTime=0,console.log(`${e.self.name} AI Started`)},t.onTick=e=>{const r=t.tree.blackboard;0!==e.errors.length&&e.errors.forEach((e=>console.log(`${e.severity}: ${e.command}: ${e.message}`))),function(e){const r=t.tree.blackboard;r.input=e,r.currentTime+=e.deltaTime;const o=function(){const e=t.tree.blackboard,r=e.input.perception.sight,o=(e.input.perception.damage,e.target?r.findIndex((t=>t.hash===e.target.hash)):-1),n=r.filter((e=>function(e,r=!1){const o=t.tree.blackboard;return[()=>e.health>0,()=>o.input.self.factionID!==e.factionID,()=>(0,s.distanceTo)(o.input.self,e)<=5e4].map((e=>e())).reduce(((e,t)=>e&&t))}(e)));if(0===n.length)return-1===o?e.target:null;const a=n.map(c);return n[a.indexOf(Math.max(...a))]}();null===o?l():r.target=o,function(){const e=t.tree.blackboard,r=e.input.perception.sight;if(void 0!==e.damageInstigatorHash&&-1!==r.findIndex((t=>t.hash===e.damageInstigatorHash&&t.health<=0))&&function(){const e=t.tree.blackboard;void 0!==e.damageStimulusTime&&delete e.damageStimulusTime,void 0!==e.damageInstigatorHash&&delete e.damageInstigatorHash,void 0!==e.damageStimulusDirection&&delete e.damageStimulusDirection,void 0!==e.damageStimulusFocalPoint&&delete e.damageStimulusFocalPoint}(),e.target){if(0===r.length)e.canSeeTarget&&(e.targetLostSightTime=e.currentTime),e.canSeeTarget=!1;else{const t=-1!==r.findIndex((t=>t.hash===e.target.hash));e.canSeeTarget&&!t&&(e.targetLostSightTime=e.currentTime),e.canSeeTarget=t,e.canSeeTarget&&(e.targetLastKnownLocation=e.target.location,e.targetPredictedLocation=e.target.location,e.targetLastKnownVelocity=e.target.velocity)}void 0!==e.targetLastKnownLocation&&(e.targetPredictedLocation=(0,s.add)(e.targetPredictedLocation,(0,s.multiply)(e.targetLastKnownVelocity,e.input.deltaTime)))}}(),function(){const e=t.tree.blackboard,r=e.input.perception.damage;if(0===r.length)return;const o=r.filter((e=>!e.friendly));if(0===o.length)return;const n=o.length-1;e.damageStimulusTime=e.currentTime,e.damageInstigatorHash=o[n].instigatorHash,e.damageStimulusDirection=o[n].damageDirection,e.damageStimulusFocalPoint=(0,s.add)(e.input.self.location,(0,s.multiply)(e.damageStimulusDirection,1e4)),e.lastHitLocation=e.input.self.location,e.isLastDamageFromTarget=e.target&&e.target.hash===o[n].instigatorHash}(),function(){const e=t.tree.blackboard,r=e.input.perception.sound;if(0===r.length)return;const o=r.filter((e=>!e.friendly)).filter((e=>"Taunt"===e.tag)),s=o.length-1;s<0||(e.heardNoise=!0,e.noiseLocation=o[s].location)}(),function(){const e=t.tree.blackboard;if(0===e.input.perception.interactable.length)return void(void 0!==e.desiredPickupLocation&&delete e.desiredPickupLocation);const r=function(){const e=t.tree.blackboard,r=function(){const e=t.tree.blackboard,r=e.input.self,o=e=>1-r.health/r.healthMax,n=e=>1-r.shield/r.shieldMax,a=e=>1-Math.min(1,(0,s.distanceToVec)(r.location,e.location)/5e4),i=[o,e=>n()-1,a],c=[e=>o()-1,n,a];let l=[];for(const t of e.input.perception.interactable){let e=0;"Pickup.Heal"===t.tag?e=i.map((e=>e(t))).reduce(((e,t)=>e+t)):"Pickup.Shield"===t.tag?e=c.map((e=>e(t))).reduce(((e,t)=>e+t)):console.log("TODO for ammo crate"),l.push(e)}return l}(),o=r.indexOf(Math.max(...r));return r[o]>0?e.input.perception.interactable[o]:void 0}();void 0!==r&&(e.desiredPickupLocation=r.location)}()}(e),r.isCommanded=n.AI.IsMoveCommanded(),n.AI.HasMoveCommandLocation()&&(r.moveCommandLocation=n.AI.GetMoveCommandLocation()),t.tree.step();for(let[t,o]of Object.entries(e.eqs))r.eqsResults[t]=o,2===o.status&&n.AI.EQS_Complete((0,i.StringToEQSQueryType)(t))},t.clearBlackboardTarget=l},"./src/predicates/Predicate_FocusToDamage.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.Predicate_FocusToDamage=void 0,t.Predicate_FocusToDamage=e=>void 0!==e.damageStimulusFocalPoint&&(void 0!==e.damageInstigatorHash&&(null===e.target||!e.canSeeTarget&&(!(e.damageStimulusTime<=e.targetLostSightTime)||!(e.currentTime-e.damageStimulusTime>=10)&&e.damageInstigatorHash!==e.target.hash)))},"./src/tasks/BTT_MeleeAttack.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_MeleeAttack=void 0;const o=r("./src/index.ts"),s=r("./node_modules/behaviortree/lib/index.js");t.BTT_MeleeAttack=e=>new s.Task({run:t=>(o.AI.WeaponTrigger(e),s.RUNNING),end:t=>{o.AI.WeaponRelease(e)},abort:t=>{o.AI.WeaponRelease(e)}})},"./src/tasks/BTT_SendMessage.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SendMessage=void 0;const o=r("./src/index.ts"),s=r("./node_modules/behaviortree/lib/index.js");t.BTT_SendMessage=e=>new s.Task({run:t=>(o.AI.SendMessage(e),s.SUCCESS)})},"./src/tasks/BTT_SetValue.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SetValue=void 0;const o=r("./node_modules/behaviortree/lib/index.js");t.BTT_SetValue=e=>new o.Task({run:t=>(e(t),o.SUCCESS)})},"./src/tasks/BTT_Shoot.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Shoot=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/index.ts");t.BTT_Shoot=e=>new o.Task({start:t=>-1!==t.input.self.weapons.findIndex((t=>t.tags.findIndex((t=>t===e))))?o.SUCCESS:o.FAILURE,run:t=>{const r=s.AI.WeaponGetAmmoByTag(e)>0;return r?s.AI.WeaponTrigger(e,t.targetLastKnownLocation):s.AI.WeaponRelease(e),r?o.RUNNING:o.FAILURE},abort:t=>{s.AI.WeaponRelease(e)}})},"./src/tasks/BTT_Success.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Success=void 0;const o=r("./node_modules/behaviortree/lib/index.js");t.BTT_Success=new o.Task({run:e=>o.SUCCESS})},"./src/tasks/BTT_Wait.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Wait=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/index.ts");t.BTT_Wait=e=>new o.Task({start:t=>s.AI.Wait(e)?o.SUCCESS:o.FAILURE,run:e=>{switch(s.AI.QueryStatus("Action.Wait")){case 0:return o.RUNNING;case 2:default:return o.FAILURE;case 1:return o.SUCCESS}}})},"./src/tasks/environment/BTT_QuerySetArgument.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_QuerySetArgumentFloat=t.BTT_QuerySetArgumentVector=t.BTT_QuerySetArgumentString=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/index.ts");t.BTT_QuerySetArgumentString=(e,t,r)=>new o.Task({run:n=>{const a=r(n);return s.AI.EQS_SetArgumentString(e,t,a),o.SUCCESS}}),t.BTT_QuerySetArgumentVector=(e,t,r)=>new o.Task({run:n=>{const a=r(n);return s.AI.EQS_SetArgumentVector(e,t,a),o.SUCCESS}}),t.BTT_QuerySetArgumentFloat=(e,t,r)=>new o.Task({run:n=>{const a=r(n);return s.AI.EQS_SetArgumentFloat(e,t,a),o.SUCCESS}})},"./src/tasks/environment/BTT_RunEQSQuery.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_RunEQSQuery=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/index.ts");t.BTT_RunEQSQuery=(e,t)=>new o.Task({start:t=>(t.eqsResults[e]={status:1},s.AI.EQS_Query(e)?o.SUCCESS:o.FAILURE),run:r=>{const s=r.eqsResults[e];if(!s)return o.FAILURE;switch(s.status){case 1:return o.RUNNING;case 3:default:return o.FAILURE;case 2:return r[t]=r.eqsResults[e].location,o.SUCCESS}}})},"./src/tasks/focus/BTT_SetFocalPoint.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SetFocalPoint=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/index.ts"),n=r("./src/utils.ts");t.BTT_SetFocalPoint=e=>new o.Task({start:t=>{const r=t[e];return r?(0,n.IsWarMachine)(r)?s.AI.SetFocalPointByHash(r.hash)?o.SUCCESS:o.FAILURE:(0,n.IsVector)(r)?s.AI.SetFocalPointByLocation(r)?o.SUCCESS:o.FAILURE:(console.log("BTT_SetFocalPoint: Invalid focal point type."),o.FAILURE):o.FAILURE},run:e=>o.SUCCESS})},"./src/tasks/movement/BTT_MoveTo.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_MoveTo=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/index.ts"),n=r("./src/utils.ts");t.BTT_MoveTo=(e,t=!1,r=600,a=20)=>new o.Task({start:t=>{const a=t[e];return a&&(0,n.IsVector)(a)&&s.AI.MoveToVector(a,r)?o.SUCCESS:o.FAILURE},run:a=>{if(t){const t=a[e];if(!t||!(0,n.IsVector)(t))return o.FAILURE;if(!s.AI.MoveToVector(t,r))return o.FAILURE}switch(s.AI.QueryMovementResult()){case 0:return o.RUNNING;case 1:return o.SUCCESS;default:return o.FAILURE}}})},"./src/trees/BT_MoveToCommand.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_MoveToCommand=void 0;const o=r("./src/tasks/BTT_SetValue.ts"),s=r("./src/tasks/movement/BTT_MoveTo.ts"),n=r("./node_modules/behaviortree/lib/index.js"),a=r("./src/tasks/BTT_SendMessage.ts");t.BT_MoveToCommand=new n.Sequence({nodes:[(0,s.BTT_MoveTo)("moveCommandLocation",!0),(0,a.BTT_SendMessage)("Message.MoveCommandComplete"),(0,o.BTT_SetValue)((e=>e.isCommanded=!1))]})},"./src/trees/BT_Patrol.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Patrol=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/tasks/movement/BTT_MoveTo.ts"),n=r("./src/tasks/environment/BTT_RunEQSQuery.ts"),a=r("./src/tasks/BTT_SetValue.ts"),i=r("./src/tasks/environment/BTT_QuerySetArgument.ts"),c=r("./src/branches/ParallelBackground.ts"),l=r("./src/trees/BT_SetFocal.ts");t.BT_Patrol=new c.ParallelBackground({nodes:[new o.Sequence({nodes:[(0,i.BTT_QuerySetArgumentVector)("patrol","Origin",(e=>e.moveCommandLocation)),(0,i.BTT_QuerySetArgumentFloat)("patrol","GridSize",(e=>3e3)),(0,i.BTT_QuerySetArgumentFloat)("patrol","SpaceBetween",(e=>1e3)),(0,n.BTT_RunEQSQuery)("patrol","patrolLocation"),(0,s.BTT_MoveTo)("patrolLocation"),(0,a.BTT_SetValue)((e=>e.patrolLocation=void 0))]}),l.BT_SetFocal]})},"./src/trees/BT_Root.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Root=t.Parallel_Patrol=t.Parallel_MoveToCommand=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/decorators/IsSet.ts"),n=r("./src/tasks/BTT_Wait.ts"),a=r("./src/trees/combat/BT_Combat.ts"),i=r("./src/trees/BT_Patrol.ts"),c=r("./src/trees/BT_MoveToCommand.ts"),l=r("./src/trees/BT_SetFocal.ts"),u=r("./src/branches/ParallelBackground.ts");t.Parallel_MoveToCommand=new u.ParallelBackground({nodes:[c.BT_MoveToCommand,l.BT_SetFocal]}),t.Parallel_Patrol=new u.ParallelBackground({nodes:[i.BT_Patrol,l.BT_SetFocal]}),t.BT_Root=new o.Selector({nodes:[(0,s.IsSet)(a.BT_Combat,"target",!0,o.ObserverAborts.Both),(0,s.IsSet)(t.Parallel_MoveToCommand,"isCommanded",!0,o.ObserverAborts.Both),(0,s.IsSet)(t.Parallel_Patrol,"moveCommandLocation",!0),(0,n.BTT_Wait)(1)]})},"./src/trees/BT_SetFocal.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_SetFocal=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/decorators/IsSet.ts"),n=r("./src/decorators/Predicate.ts"),a=r("./src/tasks/BTT_Success.ts"),i=r("./src/tasks/focus/BTT_SetFocalPoint.ts"),c=r("./src/predicates/Predicate_FocusToDamage.ts");t.BT_SetFocal=new o.Selector({nodes:[(0,s.IsSet)((0,i.BTT_SetFocalPoint)("target"),"canSeeTarget",!0,o.ObserverAborts.LowerPriority),(0,n.Predicate)((0,i.BTT_SetFocalPoint)("damageStimulusFocalPoint"),c.Predicate_FocusToDamage,!0,o.ObserverAborts.LowerPriority),(0,s.IsSet)((0,i.BTT_SetFocalPoint)("targetPredictedLocation"),"targetPredictedLocation",!0,o.ObserverAborts.LowerPriority),(0,s.IsSet)((0,i.BTT_SetFocalPoint)("targetLastKnownLocation"),"targetLastKnownLocation",!0,o.ObserverAborts.LowerPriority),a.BTT_Success]})},"./src/trees/combat/BT_CanSeeTarget.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_CanSeeTarget=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/decorators/Predicate.ts"),n=r("./src/helper.ts"),a=r("./src/trees/combat/BT_CloseCombat.ts"),i=r("./src/trees/combat/BT_RangeCombat.ts");t.BT_CanSeeTarget=new o.Selector({nodes:[(0,s.Predicate)(a.BT_CloseCombat,(e=>e.canMelee&&void 0!==e.targetLastKnownLocation&&(0,n.distanceToVec)(e.input.self.location,e.targetLastKnownLocation)<=4e3),!0,o.ObserverAborts.Both),i.BT_RangeCombat]})},"./src/trees/combat/BT_CloseCombat.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_CloseCombat=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/branches/ParallelBackground.ts"),n=r("./src/decorators/IsSet.ts"),a=r("./src/tasks/BTT_MeleeAttack.ts"),i=r("./src/tasks/BTT_Success.ts"),c=r("./src/trees/BT_SetFocal.ts"),l=r("./src/trees/BT_MoveToCommand.ts"),u=r("./src/trees/BT_Patrol.ts");t.BT_CloseCombat=new s.ParallelBackground({nodes:[(0,a.BTT_MeleeAttack)("Weapon.Melee"),c.BT_SetFocal,new o.Selector({nodes:[(0,n.IsSet)(l.BT_MoveToCommand,"isCommanded",!0,o.ObserverAborts.Both),(0,n.IsSet)(u.BT_Patrol,"moveCommandLocation",!0),i.BTT_Success]})]})},"./src/trees/combat/BT_Combat.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Combat=t.Parallel_Patrol=t.Parallel_MoveToCommand=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/decorators/IsSet.ts"),n=r("./src/trees/combat/BT_CanSeeTarget.ts"),a=r("./src/tasks/BTT_Success.ts"),i=r("./src/trees/BT_Patrol.ts"),c=r("./src/trees/BT_MoveToCommand.ts"),l=r("./src/branches/ParallelBackground.ts"),u=r("./src/trees/BT_SetFocal.ts");t.Parallel_MoveToCommand=new l.ParallelBackground({nodes:[c.BT_MoveToCommand,u.BT_SetFocal]}),t.Parallel_Patrol=new l.ParallelBackground({nodes:[i.BT_Patrol,u.BT_SetFocal]}),t.BT_Combat=new o.Selector({nodes:[(0,s.IsSet)(n.BT_CanSeeTarget,"canSeeTarget",!0,o.ObserverAborts.Both),(0,s.IsSet)(t.Parallel_MoveToCommand,"isCommanded",!0,o.ObserverAborts.Both),(0,s.IsSet)(t.Parallel_Patrol,"moveCommandLocation",!0),a.BTT_Success]})},"./src/trees/combat/BT_RangeCombat.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_RangeCombat=void 0;const o=r("./node_modules/behaviortree/lib/index.js"),s=r("./src/branches/ParallelBackground.ts"),n=r("./src/decorators/IsSet.ts"),a=r("./src/tasks/BTT_Shoot.ts"),i=r("./src/tasks/BTT_Success.ts"),c=r("./src/trees/BT_SetFocal.ts"),l=r("./src/trees/BT_MoveToCommand.ts"),u=r("./src/trees/BT_Patrol.ts");t.BT_RangeCombat=new s.ParallelBackground({nodes:[new o.Parallel({nodes:[(0,a.BTT_Shoot)("Weapon.Primary.LeftArm"),(0,a.BTT_Shoot)("Weapon.Primary.RightArm")]}),c.BT_SetFocal,new o.Selector({nodes:[(0,n.IsSet)(l.BT_MoveToCommand,"isCommanded",!0,o.ObserverAborts.Both),(0,n.IsSet)(u.BT_Patrol,"moveCommandLocation",!0),i.BTT_Success]})]})},"./src/utils.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.IsWarMachine=t.IsVector=t.StringToEQSQueryType=void 0,t.StringToEQSQueryType=e=>{switch(e){case"away":return"away";case"cover":return"cover";case"hidden":return"hidden";case"patrol":return"patrol";case"strafe":return"strafe"}},t.IsVector=e=>"X"in e&&"Y"in e,t.IsWarMachine=e=>"hash"in e}},t={};!function r(o){var s=t[o];if(void 0!==s)return s.exports;var n=t[o]={exports:{}};return e[o](n,n.exports,r),n.exports}("./src/mech.ts")})();
//# sourceMappingURL=mech.js.map