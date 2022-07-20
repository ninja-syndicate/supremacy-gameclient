/*! For license information please see mech.js.LICENSE.txt */
(()=>{var e={"./node_modules/behaviortree/lib/index.js":e=>{var t,r=Object.defineProperty,s=Object.defineProperties,o=Object.getOwnPropertyDescriptor,n=Object.getOwnPropertyDescriptors,a=Object.getOwnPropertyNames,i=Object.getOwnPropertySymbols,c=Object.prototype.hasOwnProperty,l=Object.prototype.propertyIsEnumerable,u=(e,t,s)=>t in e?r(e,t,{enumerable:!0,configurable:!0,writable:!0,value:s}):e[t]=s,d=(e,t)=>{for(var r in t||(t={}))c.call(t,r)&&u(e,r,t[r]);if(i)for(var r of i(t))l.call(t,r)&&u(e,r,t[r]);return e},T=(e,t)=>s(e,n(t)),h=(e,t)=>{var r={};for(var s in e)c.call(e,s)&&t.indexOf(s)<0&&(r[s]=e[s]);if(null!=e&&i)for(var s of i(e))t.indexOf(s)<0&&l.call(e,s)&&(r[s]=e[s]);return r},S=(e,t)=>{for(var s in t)r(e,s,{get:t[s],enumerable:!0})},p=(t="undefined"!=typeof WeakMap?new WeakMap:0,(e,s)=>t&&t.get(e)||(s=((e,t,s,n)=>{if(t&&"object"==typeof t||"function"==typeof t)for(let s of a(t))!c.call(e,s)&&r(e,s,{get:()=>t[s],enumerable:!(n=o(t,s))||n.enumerable});return e})(r({},"__esModule",{value:!0}),e),t&&t.set(e,s),s)),_={};S(_,{BehaviorTree:()=>w,BehaviorTreeImporter:()=>q,BranchNode:()=>D,Decorator:()=>j,FAILURE:()=>f,Introspector:()=>K,Node:()=>A,ObserverAborts:()=>U,Parallel:()=>G,ParallelComplete:()=>Z,ParallelSelector:()=>X,RUNNING:()=>b,Random:()=>V,SUCCESS:()=>g,Selector:()=>W,Sequence:()=>H,Task:()=>L,decorators:()=>C,default:()=>Y,getRegistry:()=>R,registryLookUp:()=>I});var b=Symbol("running"),g=!0,f=!1;function m(e){return e===b||"object"==typeof e&&e.total===b}var v=()=>!1,B=()=>!0,y=()=>{},k=()=>{},A=class{constructor(e){this.nodeType="Node",this.ranStart=!1;var t=e,{run:r=v,start:s=B,end:o=y,abort:n=k}=t,a=h(t,["run","start","end","abort"]);this.blueprint=d({run:r,start:s,end:o,abort:n},a)}run(e,t={}){var r=t,{introspector:s,rerun:o=!1,registryLookUp:n=(e=>e)}=r,a=h(r,["introspector","rerun","registryLookUp"]);if(!o||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===f)return t}let i=this.blueprint.run(e,T(d({},a),{rerun:o,registryLookUp:n}));return i!==b&&this.blueprint.end(e),s&&s.push(this,i,e),i}abort(e,{registryLookUp:t=(e=>e),lastRun:r}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:r})}get name(){return this._name||this.blueprint.name}set name(e){this._name=e}},L=class extends A{constructor(){super(...arguments),this.nodeType="Task"}},P={};function R(){return P}function I(e){if("string"==typeof e){let t=P[e];if(!t)throw new Error(`No node with name ${e} registered.`);return t}return e}var w=class{constructor({tree:e,blackboard:t}){this.tree=e,this.blackboard=t,this.lastResult=void 0}step({introspector:e}={}){let t=this.lastResult&&"object"==typeof this.lastResult?this.lastResult:void 0,r=m(this.lastResult);e&&e.start(this),this.lastResult=I(this.tree).run(this.blackboard,{lastRun:t,introspector:e,rerun:r,registryLookUp:I}),e&&e.end()}static register(e,t){P[e]="function"==typeof t?new L({name:e,run:t}):t}static cleanRegistry(){P={}}},C={};S(C,{AlwaysFailDecorator:()=>E,AlwaysSucceedDecorator:()=>F,CooldownDecorator:()=>O,InvertDecorator:()=>N,LoopDecorator:()=>Q});var M,U=((M=U||{})[M.None=0]="None",M[M.Self=1]="Self",M[M.LowerPriority=2]="LowerPriority",M[M.Both=3]="Both",M),x=e=>"observerAborts"in e,j=class extends A{constructor(e={config:{}}){var t=e,{config:r={}}=t;super(h(t,["config"])),this.nodeType="Decorator",this.observerAborts=0,this.setConfig(r)}condition(e){return g}decorate(e,t,r,s){return this.condition(t)||s&&1!==this.observerAborts&&3!==this.observerAborts?e(e,t,r):f}run(e,t={}){var r=t,{introspector:s,rerun:o,registryLookUp:n=(e=>e)}=r,a=h(r,["introspector","rerun","registryLookUp"]);if(!o||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===f)return t}let i=0,c=this.decorate((()=>(++i,n(this.blueprint.node).run(e,T(d({},a),{rerun:o,introspector:s,registryLookUp:n})))),e,this.config,o);return c!==b&&(this.blueprint.end(e),void 0!==(c===f&&this.blueprint.node)&&this.blueprint.node.blueprint.end(e)),s&&s.wrapLast(i,this,c,e),c}abort(e,{registryLookUp:t=(e=>e),lastRun:r}={}){super.abort(e,{registryLookUp:t,lastRun:r}),void 0!==this.blueprint.node&&this.blueprint.node.abort(e,{registryLookUp:t,lastRun:r})}setConfig(e){this.config=e}},E=class extends j{constructor(){super(...arguments),this.nodeType="AlwaysFailDecorator"}decorate(e){let t=e();return m(t)?t:f}},F=class extends j{constructor(){super(...arguments),this.nodeType="AlwaysSucceedDecorator"}decorate(e){let t=e();return m(t)?t:g}},O=class extends j{constructor(){super(...arguments),this.lock=!1,this.nodeType="CooldownDecorator"}setConfig({cooldown:e=5}){this.config={cooldown:e}}decorate(e){if(this.lock)return f;let t=e();return m(t)||(this.lock=!0,setTimeout((()=>{this.lock=!1}),1e3*this.config.cooldown)),t}},N=class extends j{constructor(){super(...arguments),this.nodeType="InvertDecorator"}decorate(e){let t=e();return m(t)?t:t===g?f:g}},Q=class extends j{constructor(){super(...arguments),this.nodeType="LoopDecorator"}setConfig({loop:e=1/0}){this.config={loop:e}}decorate(e){let t=0,r=f;for(;t++<this.config.loop;)if(r=e(),r===f)return f;return r}},D=class extends A{constructor(e){super(e),this.OPT_OUT_CASE=g,this.START_CASE=g,this.nodeType="BranchNode",this.nodes=e.nodes||[],this.numNodes=this.nodes.length,this.observedDecorators=new Map}run(e={},{lastRun:t,introspector:r,rerun:s,registryLookUp:o=(e=>e)}={}){if(!s||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===f)return t}let n=this.START_CASE,a=[],i="object"==typeof t&&t.state||[],c=Math.max(i.findIndex((e=>m(e))),0),l=0;for(;l<this.numNodes;++l){let t=!1;if(s&&this.observedDecorators.has(l))t=!0;else if(l<c){a[l]=i[l];continue}let u=o(this.nodes[l]);if(t&&x(u))if(this.observedDecorators.get(l)===u.condition(e)){if(s&&l<c){a[l]=i[l];continue}}else o(this.nodes[c]).abort(e,{registryLookUp:o,lastRun:i[c]}),c=0;let d=u.run(e,{lastRun:i[l],introspector:r,rerun:s,registryLookUp:o});if(a[l]=d,x(u)&&u.observerAborts>0&&this.observedDecorators.set(l,u.condition(e)),d===b||"object"==typeof d){n=b;break}if(d===this.OPT_OUT_CASE){n=d;break}s=!1}let u=m(n);if(u||this.blueprint.end(e),r){let t=u?b:n;r.wrapLast(Math.min(l+1,this.numNodes),this,t,e)}return n===b?{total:n,state:a}:n}abort(e={},{lastRun:t,registryLookUp:r=(e=>e)}={}){super.abort(e,{registryLookUp:r,lastRun:t});let s="object"==typeof t&&t.state||[],o=Math.max(s.findIndex((e=>m(e))),0);r(this.nodes[o]).abort(e,{registryLookUp:r,lastRun:s[o]})}},V=class extends D{constructor(){super(...arguments),this.nodeType="Random"}run(e={},{lastRun:t,introspector:r,rerun:s,registryLookUp:o=(e=>e)}={}){let n=0;s?n=t.state.findIndex((e=>m(e))):(this.blueprint.start(e),n=Math.floor(Math.random()*this.numNodes));let a=o(this.nodes[n]).run(e,{lastRun:t,introspector:r,rerun:s,registryLookUp:o}),i=m(a);if(i||this.blueprint.end(e),r){let t=i?b:a;r.wrapLast(1,this,t,e)}if(i){let e={total:b,state:new Array(this.numNodes).fill(void 0)};return e.state[n]=a,e}return a}},W=class extends D{constructor(){super(...arguments),this.nodeType="Selector",this.START_CASE=f,this.OPT_OUT_CASE=g}},H=class extends D{constructor(){super(...arguments),this.nodeType="Sequence",this.START_CASE=g,this.OPT_OUT_CASE=f}},q=class{constructor(){this.types={task:L,decorator:j,selector:W,sequence:H,random:V,invert:N,fail:E,succeed:F,cooldown:O,loop:Q}}defineType(e,t){this.types[e]=t}parse(e){let t=e,{type:r,name:s}=t,o=h(t,["type","name"]),n=this.types[r];if(!n){let e=I(r);if(e)return e.name=s,e;throw new Error(`Don't know how to handle type ${r}. Please register this first.`)}return new n({name:s,node:e.node?this.parse(e.node):null,nodes:e.nodes?e.nodes.map((e=>this.parse(e))):null,config:o})}},K=class{constructor(){this.currentResult=[],this.results=[]}start(e){this.tree=e,this.currentResult=[]}end(){let e=this.currentResult.pop();e&&this.results.push(e),delete this.tree,this.currentResult=[]}push(e,t,r){this.currentResult.push(this._toResult(e,t,r))}wrapLast(e,t,r,s){let o=this.currentResult.splice(this.currentResult.length-e,e);this.currentResult.push(T(d({},this._toResult(t,r,s)),{children:o}))}_toResult(e,t,r){return T(d({},e.name?{name:e.name}:{}),{result:t})}reset(){this.results=[]}get lastResult(){return 0===this.results.length?null:this.results[this.results.length-1]}},G=class extends D{constructor(e){super(e),this.nodeType="Parallel",this.nodes=e.nodes||[],this.numNodes=this.nodes.length}run(e={},{lastRun:t,introspector:r,rerun:s,registryLookUp:o=(e=>e)}={}){if(!s||!this.ranStart){this.ranStart=!0;let t=this.blueprint.start(e);if(t===f)return t}let n=[];for(let a=0;a<this.numNodes;++a){let i=t&&t.state[a];if(i&&!m(i)){n[a]=i;continue}let c=o(this.nodes[a]).run(e,{lastRun:i,introspector:r,rerun:s,registryLookUp:o});n[a]=c}let a=this.calcResult(n);if(m(a)||this.blueprint.end(e),r){let t=n.find((e=>m(e)))?b:a;r.wrapLast(this.numNodes,this,t,e)}return a}calcResult(e){return e.includes(f)?f:e.find((e=>m(e)))?{total:b,state:e}:g}abort(e,{registryLookUp:t=(e=>e),lastRun:r}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:r});for(let s of this.nodes)s.abort(e,{registryLookUp:t,lastRun:r})}},Z=class extends G{constructor(){super(...arguments),this.nodeType="ParallelComplete"}calcResult(e){return e.includes(f)?f:e.includes(g)?g:{total:b,state:e}}},X=class extends G{constructor(){super(...arguments),this.nodeType="ParallelSelector"}calcResult(e){return e.includes(f)?f:e.find((e=>m(e)))?{total:b,state:e}:g}},Y=w;e.exports=p(_)},"./src/branches/ParallelBackground.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.ParallelBackground=void 0;const s=r("./node_modules/behaviortree/lib/index.js");class o extends s.Parallel{constructor(){super(...arguments),this.nodeType="ParallelBackground"}run(e={},{lastRun:t,introspector:r,rerun:o,registryLookUp:c=(e=>e)}={}){const l=[];let u=!1;if(this.ranStart)for(let r=1;r<this.numNodes;++r){let o=t&&t.state[r];if(o&&i(o)){const t=c(this.nodes[r]).blueprint.start(e);if(t===s.FAILURE){l[r]=t,u=!0;break}}}if(!o||!this.ranStart){this.ranStart=!0;const t=this.blueprint.start(e);if(t===s.FAILURE)return t}if(!u)for(let s=0;s<this.numNodes;++s){let u=t&&t.state[s];if(u&&!n(u)){if(l[s]=u,0===s)break;if(a(u))break}const d=c(this.nodes[s]),T=!i(u)&&o,h=!i(u)&&u,S=d.run(e,{lastRun:h,introspector:r,rerun:T,registryLookUp:c});if(l[s]=S,0===s&&a(S))break}const d=this.calcResult(l);if((a(d)||i(l[0]))&&this.blueprint.end(e),r){const t=l.find((e=>n(e)))?s.RUNNING:d;r.wrapLast(this.numNodes,this,t,e)}return i(l[0])?s.SUCCESS:d}abort(e,{registryLookUp:t=(e=>e),lastRun:r}={}){this.blueprint.abort(e,{registryLookUp:t,lastRun:r});for(const s of this.nodes)s.abort(e,{registryLookUp:t,lastRun:r})}calcResult(e){return e.includes(s.FAILURE)?s.FAILURE:{total:s.RUNNING,state:e}}}function n(e){return e===s.RUNNING||"object"==typeof e&&e.total===s.RUNNING}function a(e){return e===s.FAILURE||"object"==typeof e&&e.total===s.FAILURE}function i(e){return e===s.SUCCESS||"object"==typeof e&&e.total===s.SUCCESS}t.ParallelBackground=o},"./src/decorators/CanActivateAction.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.CanActivateAction=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts");class n extends s.Decorator{constructor(){super(...arguments),this.nodeType="CanActivateActionDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}condition(e){return!!o.AI.CanActivateAction(this.config.action)===this.config.isMatch}}t.CanActivateAction=(e,t,r=!0,o=s.ObserverAborts.None)=>new n({node:e,config:{action:t,isMatch:r,observerAborts:o}})},"./src/decorators/IsSet.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.IsSet=void 0;const s=r("./node_modules/behaviortree/lib/index.js");class o extends s.Decorator{constructor(){super(...arguments),this.nodeType="IsSetDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}condition(e){return!!e[this.config.blackboardKey]===this.config.isSet}}t.IsSet=(e,t,r=!0,n=s.ObserverAborts.None)=>new o({node:e,config:{blackboardKey:t,isSet:r,observerAborts:n}})},"./src/decorators/Predicate.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.Predicate=void 0;const s=r("./node_modules/behaviortree/lib/index.js");class o extends s.Decorator{constructor(){super(...arguments),this.nodeType="PredicateDecorator"}setConfig(e){this.config=e,this.observerAborts=e.observerAborts}condition(e){return!!this.config.predicate(e)===this.config.isMatch}}t.Predicate=(e,t,r=!0,n=s.ObserverAborts.None)=>new o({node:e,config:{predicate:t,isMatch:r,observerAborts:n}})},"./src/helper.ts":(e,t)=>{"use strict";function r(e,t){const{X:r,Y:s,Z:o}=e,{X:n,Y:a,Z:i}=t,c={X:n-r,Y:a-s,Z:i-o};return Math.sqrt(Math.pow(c.X,2)+Math.pow(c.Y,2)+Math.pow(c.Z,2))}function s(e,t){Math.abs(t);const r=e/t;return e-t*Math.trunc(r)}Object.defineProperty(t,"__esModule",{value:!0}),t.getForwardVector=t.fmod=t.rotateZ=t.multiply=t.add=t.distanceToVec=t.distanceTo=t.isDead=void 0,t.isDead=function(e){return e.health<=0},t.distanceTo=function(e,t){return r(e.location,t.location)},t.distanceToVec=r,t.add=function(e,t){const{X:r,Y:s,Z:o}=e,{X:n,Y:a,Z:i}=t;return{X:r+n,Y:s+a,Z:o+i}},t.multiply=function(e,t){const{X:r,Y:s,Z:o}=e;return{X:r*t,Y:s*t,Z:o*t}},t.rotateZ=function(e,t){const r=t*(Math.PI/180),{X:s,Y:o,Z:n}=e;return{X:s*Math.cos(r)-o*Math.sin(r),Y:s*Math.sin(r)+o*Math.cos(r),Z:n}},t.fmod=s,t.getForwardVector=function(e){const{X:t,Y:r,Z:o}=e,n=e=>e*(Math.PI/180),a=s(r,360),i=s(o,360),c=Math.sin(n(a)),l=Math.cos(n(a)),u=Math.sin(n(i));return{X:l*Math.cos(n(i)),Y:l*u,Z:c}}},"./src/index.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.AI=void 0;const s=r("./src/mech.ts");t.AI=Context.GetOwner(),Context.OnMessage=(e,t)=>{try{switch(e){case"onTick":(0,s.onTick)(JSON.parse(t));break;case"onBegin":(0,s.onBegin)(JSON.parse(t))}}catch(e){console.log(e)}}},"./src/mech.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.clearBlackboardTarget=t.onTick=t.onBegin=t.tree=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/helper.ts"),n=r("./src/index.ts"),a=r("./src/trees/BT_Root.ts"),i=r("./src/utils.ts");function c(e){const r=t.tree.blackboard,s=[e=>1-(e.health+e.shield)/(e.healthMax+e.shieldMax),e=>1-Math.min(1,(0,o.distanceTo)(r.input.self,e)/5e4)];return s.map((t=>t(e))).reduce(((e,t)=>e+t))/s.length}function l(){const e=t.tree.blackboard;e.target=null,e.canSeeTarget=!1,void 0!==e.targetLostSightTime&&delete e.targetLostSightTime,void 0!==e.targetLastKnownLocation&&delete e.targetLastKnownLocation,void 0!==e.targetPredictedLocation&&delete e.targetPredictedLocation}t.tree=new s.BehaviorTree({tree:a.BT_Root,blackboard:{target:null,eqsResults:{}}}),t.onBegin=e=>{const r=t.tree.blackboard;for(let t of e.self.weapons)if(void 0!==t.tags.find((e=>"Weapon.Secondary"===e))){r.secondaryWeapon=t,r.canUseSpecialAttack=!0;break}for(let t of e.self.weapons)if(void 0!==t.tags.find((e=>"Weapon.Melee"===e))){r.canMelee=!0;break}r.currentTime=0,console.log(`${e.self.name} AI Started`)},t.onTick=e=>{const r=t.tree.blackboard;0!==e.errors.length&&e.errors.forEach((e=>console.log(`${e.severity}: ${e.command}: ${e.message}`))),function(e){const r=t.tree.blackboard;r.input=e,r.currentTime+=e.deltaTime;const s=function(){const e=t.tree.blackboard,r=e.input.perception.sight,s=(e.input.perception.damage,e.target?r.findIndex((t=>t.hash===e.target.hash)):-1),n=r.filter((e=>function(e,r=!1){const s=t.tree.blackboard;return[()=>e.health>0,()=>(0,o.distanceTo)(s.input.self,e)<=5e4].map((e=>e())).reduce(((e,t)=>e&&t))}(e)));if(0===n.length)return-1===s?e.target:null;const a=n.map(c);return n[a.indexOf(Math.max(...a))]}();null===s?l():r.target=s,function(){const e=t.tree.blackboard,r=e.input.perception.sight;if(void 0!==e.damageInstigatorHash&&-1!==r.findIndex((t=>t.hash===e.damageInstigatorHash&&t.health<=0))&&function(){const e=t.tree.blackboard;void 0!==e.damageStimulusTime&&delete e.damageStimulusTime,void 0!==e.damageInstigatorHash&&delete e.damageInstigatorHash,void 0!==e.damageStimulusDirection&&delete e.damageStimulusDirection,void 0!==e.damageStimulusFocalPoint&&delete e.damageStimulusFocalPoint}(),e.target){if(0===r.length)e.canSeeTarget&&(e.targetLostSightTime=e.currentTime),e.canSeeTarget=!1;else{const t=-1!==r.findIndex((t=>t.hash===e.target.hash));e.canSeeTarget&&!t&&(e.targetLostSightTime=e.currentTime),e.canSeeTarget=t,e.canSeeTarget&&(e.targetLastKnownLocation=e.target.location,e.targetPredictedLocation=e.target.location,e.targetLastKnownVelocity=e.target.velocity)}void 0!==e.targetLastKnownLocation&&(e.targetPredictedLocation=(0,o.add)(e.targetPredictedLocation,(0,o.multiply)(e.targetLastKnownVelocity,e.input.deltaTime)))}}(),function(){const e=t.tree.blackboard,r=e.input.perception.damage;if(0===r.length)return;const s=r.filter((e=>!e.friendly));if(0===s.length)return;const n=s.length-1;e.damageStimulusTime=e.currentTime,e.damageInstigatorHash=s[n].instigatorHash,e.damageStimulusDirection=s[n].damageDirection,e.damageStimulusFocalPoint=(0,o.add)(e.input.self.location,(0,o.multiply)(e.damageStimulusDirection,1e4)),e.lastHitLocation=e.input.self.location,e.isLastDamageFromTarget=e.target&&e.target.hash===s[n].instigatorHash}(),function(){const e=t.tree.blackboard,r=e.input.perception.sound;if(0===r.length)return;const s=r.filter((e=>"Taunt"===e.tag)),o=s.length-1;o<0||(e.heardNoise=!0,e.noiseLocation=s[o].location)}(),function(){const e=t.tree.blackboard;if(0===e.input.perception.interactable.length)return void(void 0!==e.desiredPickupLocation&&delete e.desiredPickupLocation);const r=function(){const e=t.tree.blackboard,r=function(){const e=t.tree.blackboard,r=e.input.self,s=e=>1-r.health/r.healthMax,n=e=>1-r.shield/r.shieldMax,a=e=>1-Math.min(1,(0,o.distanceToVec)(r.location,e.location)/5e4),i=[s,e=>n()-1,a],c=[e=>s()-1,n,a];let l=[];for(const t of e.input.perception.interactable){let e=0;"Pickup.Heal"===t.tag?e=i.map((e=>e(t))).reduce(((e,t)=>e+t)):"Pickup.Shield"===t.tag?e=c.map((e=>e(t))).reduce(((e,t)=>e+t)):console.log("TODO for ammo crate"),l.push(e)}return l}(),s=r.indexOf(Math.max(...r));return r[s]>0?e.input.perception.interactable[s]:void 0}();void 0!==r&&(e.desiredPickupLocation=r.location)}()}(e),t.tree.step();for(let[t,s]of Object.entries(e.eqs))r.eqsResults[t]=s,2===s.status&&n.AI.EQS_Complete((0,i.StringToEQSQueryType)(t))},t.clearBlackboardTarget=l},"./src/predicates/Predicate_FocusToDamage.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.Predicate_FocusToDamage=void 0,t.Predicate_FocusToDamage=e=>void 0!==e.damageStimulusFocalPoint&&(void 0!==e.damageInstigatorHash&&(null===e.target||!e.canSeeTarget&&(!(e.damageStimulusTime<=e.targetLostSightTime)||!(e.currentTime-e.damageStimulusTime>=10)&&e.damageInstigatorHash!==e.target.hash)))},"./src/tasks/BTT_ClearTarget.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_ClearTarget=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/mech.ts");t.BTT_ClearTarget=new s.Task({run:e=>((0,o.clearBlackboardTarget)(),s.SUCCESS)})},"./src/tasks/BTT_LookAt.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_LookAt=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts"),n=r("./src/utils.ts");t.BTT_LookAt=e=>new s.Task({start:t=>{const r=t[e];if(r&&(0,n.IsVector)(r))return o.AI.LookAt(r)?s.SUCCESS:s.FAILURE},run:e=>{switch(o.AI.QueryStatus("Action.LookAt")){case 0:return s.RUNNING;case 2:default:return s.FAILURE;case 1:return s.SUCCESS}}})},"./src/tasks/BTT_MeleeAttack.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_MeleeAttack=void 0;const s=r("./src/index.ts"),o=r("./node_modules/behaviortree/lib/index.js");t.BTT_MeleeAttack=e=>new o.Task({run:t=>(s.AI.WeaponTrigger(e),o.RUNNING),end:t=>{s.AI.WeaponRelease(e)},abort:t=>{s.AI.WeaponRelease(e)}})},"./src/tasks/BTT_SetValue.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SetValue=void 0;const s=r("./node_modules/behaviortree/lib/index.js");t.BTT_SetValue=e=>new s.Task({run:t=>(e(t),s.SUCCESS)})},"./src/tasks/BTT_Shoot.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Shoot=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts");t.BTT_Shoot=e=>new s.Task({start:t=>-1!==t.input.self.weapons.findIndex((t=>t.tags.findIndex((t=>t===e))))?s.SUCCESS:s.FAILURE,run:t=>{const r=o.AI.WeaponGetAmmoByTag(e)>0;return r?o.AI.WeaponTrigger(e,t.targetLastKnownLocation):o.AI.WeaponRelease(e),r?s.RUNNING:s.FAILURE},abort:t=>{o.AI.WeaponRelease(e)}})},"./src/tasks/BTT_SpecialAttack.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SpecialAttack=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts"),n=r("./src/utils.ts");t.BTT_SpecialAttack=e=>new s.Task({start:t=>{const r=t[e];return r&&(0,n.IsVector)(r)?void 0===t.secondaryWeapon||null===t.secondaryWeapon?s.FAILURE:o.AI.TrySpecialAttack(r)?s.SUCCESS:s.FAILURE:s.FAILURE},run:e=>{switch(o.AI.QueryStatus("Action.SpecialAttack")){case 0:return s.RUNNING;case 2:default:return s.FAILURE;case 1:return s.SUCCESS}}})},"./src/tasks/BTT_Success.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Success=void 0;const s=r("./node_modules/behaviortree/lib/index.js");t.BTT_Success=new s.Task({run:e=>s.SUCCESS})},"./src/tasks/BTT_Taunt.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Taunt=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts");t.BTT_Taunt=new s.Task({start:e=>o.AI.Taunt()?s.SUCCESS:s.FAILURE,run:e=>{switch(o.AI.QueryStatus("Action.Taunt")){case 0:return s.RUNNING;case 2:default:return s.FAILURE;case 1:return s.SUCCESS}}})},"./src/tasks/BTT_Wait.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_Wait=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts");t.BTT_Wait=e=>new s.Task({start:t=>o.AI.Wait(e)?s.SUCCESS:s.FAILURE,run:e=>{switch(o.AI.QueryStatus("Action.Wait")){case 0:return s.RUNNING;case 2:default:return s.FAILURE;case 1:return s.SUCCESS}}})},"./src/tasks/environment/BTT_QuerySetArgument.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_QuerySetArgumentFloat=t.BTT_QuerySetArgumentVector=t.BTT_QuerySetArgumentString=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts");t.BTT_QuerySetArgumentString=(e,t,r)=>new s.Task({run:n=>{const a=r(n);return o.AI.EQS_SetArgumentString(e,t,a),s.SUCCESS}}),t.BTT_QuerySetArgumentVector=(e,t,r)=>new s.Task({run:n=>{const a=r(n);return o.AI.EQS_SetArgumentVector(e,t,a),s.SUCCESS}}),t.BTT_QuerySetArgumentFloat=(e,t,r)=>new s.Task({run:n=>{const a=r(n);return o.AI.EQS_SetArgumentFloat(e,t,a),s.SUCCESS}})},"./src/tasks/environment/BTT_RunEQSQuery.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_RunEQSQuery=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts");t.BTT_RunEQSQuery=(e,t)=>new s.Task({start:t=>(t.eqsResults[e]={status:1},o.AI.EQS_Query(e),s.SUCCESS),run:r=>{const o=r.eqsResults[e];if(!o)return s.FAILURE;switch(o.status){case 1:return s.RUNNING;case 3:default:return s.FAILURE;case 2:return r[t]=r.eqsResults[e].location,s.SUCCESS}}})},"./src/tasks/focus/BTT_SetFocalPoint.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_SetFocalPoint=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts"),n=r("./src/utils.ts");t.BTT_SetFocalPoint=e=>new s.Task({start:t=>{const r=t[e];return r?(0,n.IsWarMachine)(r)?o.AI.SetFocalPointByHash(r.hash)?s.SUCCESS:s.FAILURE:(0,n.IsVector)(r)?o.AI.SetFocalPointByLocation(r)?s.SUCCESS:s.FAILURE:(console.log("BTT_SetFocalPoint: Invalid focal point type."),s.FAILURE):s.FAILURE},run:e=>s.SUCCESS})},"./src/tasks/movement/BTT_MoveTo.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_MoveTo=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts"),n=r("./src/utils.ts");t.BTT_MoveTo=(e,t=!1,r=800,a=20)=>new s.Task({start:t=>{const a=t[e];return a&&(0,n.IsVector)(a)&&o.AI.MoveToVector(a,r)?s.SUCCESS:s.FAILURE},run:a=>{if(t){const t=a[e];if(!t||!(0,n.IsVector)(t))return s.FAILURE;if(!o.AI.MoveToVector(t,r))return s.FAILURE}switch(o.AI.QueryMovementResult()){case 0:return s.RUNNING;case 1:return s.SUCCESS;default:return s.FAILURE}}})},"./src/tasks/movement/BTT_StopMoveTo.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BTT_StopMoveTo=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/index.ts");t.BTT_StopMoveTo=new s.Task({run:e=>(o.AI.StopMoveTo(),s.SUCCESS)})},"./src/trees/BT_InvestigateNoise.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_InvestigateNoise=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/tasks/movement/BTT_MoveTo.ts"),n=r("./src/tasks/BTT_SetValue.ts"),a=r("./src/trees/BT_SearchHiddenLocation.ts"),i=r("./src/branches/ParallelBackground.ts"),c=r("./src/trees/BT_SetFocal.ts");t.BT_InvestigateNoise=new i.ParallelBackground({nodes:[new s.Sequence({nodes:[(0,o.BTT_MoveTo)("noiseLocation"),(0,a.BT_SearchHiddenLocation)("noiseLocation"),(0,n.BTT_SetValue)((e=>e.noiseLocation=void 0)),(0,n.BTT_SetValue)((e=>e.heardNoise=!1))]}),c.BT_SetFocal]})},"./src/trees/BT_Patrol.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Patrol=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/tasks/movement/BTT_MoveTo.ts"),n=r("./src/tasks/environment/BTT_RunEQSQuery.ts"),a=r("./src/tasks/BTT_SetValue.ts"),i=r("./src/tasks/environment/BTT_QuerySetArgument.ts"),c=r("./src/branches/ParallelBackground.ts"),l=r("./src/trees/BT_SetFocal.ts");t.BT_Patrol=new c.ParallelBackground({nodes:[new s.Sequence({nodes:[(0,i.BTT_QuerySetArgumentVector)("patrol","Origin",(e=>e.input.self.location)),(0,i.BTT_QuerySetArgumentFloat)("patrol","GridSize",(e=>15e3)),(0,i.BTT_QuerySetArgumentFloat)("patrol","SpaceBetween",(e=>1e3)),(0,n.BTT_RunEQSQuery)("patrol","patrolLocation"),(0,o.BTT_MoveTo)("patrolLocation"),(0,a.BTT_SetValue)((e=>e.patrolLocation=void 0))]}),l.BT_SetFocal]})},"./src/trees/BT_ReceivedDamage.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_ReceivedDamage=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/branches/ParallelBackground.ts"),n=r("./src/helper.ts"),a=r("./src/tasks/BTT_LookAt.ts"),i=r("./src/tasks/BTT_SetValue.ts"),c=r("./src/tasks/movement/BTT_StopMoveTo.ts"),l=r("./src/trees/BT_SearchHiddenLocation.ts"),u=r("./src/trees/BT_SetFocal.ts");t.BT_ReceivedDamage=new s.Sequence({nodes:[c.BTT_StopMoveTo,(0,a.BTT_LookAt)("damageStimulusFocalPoint"),new o.ParallelBackground({nodes:[new s.Sequence({nodes:[(0,i.BTT_SetValue)((e=>e.damageStimulusFocalPoint=void 0)),(0,i.BTT_SetValue)((e=>e.damageHiddenLocation=(0,n.add)(e.input.self.location,(0,n.multiply)(e.damageStimulusDirection,1e4)))),(0,l.BT_SearchHiddenLocation)("damageHiddenLocation"),(0,i.BTT_SetValue)((e=>e.damageHiddenLocation=void 0))]}),u.BT_SetFocal]})]})},"./src/trees/BT_Root.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Root=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/decorators/CanActivateAction.ts"),n=r("./src/decorators/IsSet.ts"),a=r("./src/tasks/BTT_Taunt.ts"),i=r("./src/tasks/BTT_Wait.ts"),c=r("./src/trees/combat/BT_Combat.ts"),l=r("./src/trees/BT_InvestigateNoise.ts"),u=r("./src/trees/BT_Patrol.ts"),d=r("./src/trees/BT_ReceivedDamage.ts");t.BT_Root=new s.Selector({nodes:[(0,n.IsSet)(c.BT_Combat,"target",!0,s.ObserverAborts.Both),(0,o.CanActivateAction)(a.BTT_Taunt,"Action.Taunt"),(0,n.IsSet)(d.BT_ReceivedDamage,"damageStimulusFocalPoint",!0,s.ObserverAborts.LowerPriority),(0,n.IsSet)(l.BT_InvestigateNoise,"heardNoise",!0,s.ObserverAborts.LowerPriority),u.BT_Patrol,(0,i.BTT_Wait)(1)]})},"./src/trees/BT_SearchHiddenLocation.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_SearchHiddenLocation=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/tasks/environment/BTT_QuerySetArgument.ts"),n=r("./src/tasks/movement/BTT_MoveTo.ts"),a=r("./src/tasks/environment/BTT_RunEQSQuery.ts"),i=r("./src/tasks/BTT_SetValue.ts"),c=r("./src/tasks/focus/BTT_SetFocalPoint.ts");t.BT_SearchHiddenLocation=e=>new s.Sequence({nodes:[(0,o.BTT_QuerySetArgumentVector)("hidden","TargetPredictedLocation",(t=>t[e])),(0,a.BTT_RunEQSQuery)("hidden","hiddenLocation"),(0,c.BTT_SetFocalPoint)("hiddenLocation"),(0,n.BTT_MoveTo)("hiddenLocation"),(0,i.BTT_SetValue)((e=>e.hiddenLocation=void 0))]})},"./src/trees/BT_SearchTarget.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_SearchTarget=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/branches/ParallelBackground.ts"),n=r("./src/decorators/IsSet.ts"),a=r("./src/tasks/BTT_ClearTarget.ts"),i=r("./src/tasks/movement/BTT_MoveTo.ts"),c=r("./src/trees/BT_SetFocal.ts"),l=r("./src/trees/BT_SearchHiddenLocation.ts");t.BT_SearchTarget=new s.Sequence({nodes:[new o.ParallelBackground({nodes:[new s.Sequence({nodes:[(0,n.IsSet)((0,i.BTT_MoveTo)("targetLastKnownLocation"),"targetLastKnownLocation"),(0,n.IsSet)((0,l.BT_SearchHiddenLocation)("targetPredictedLocation"),"targetPredictedLocation")]}),c.BT_SetFocal]}),a.BTT_ClearTarget]})},"./src/trees/BT_SetFocal.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_SetFocal=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/decorators/IsSet.ts"),n=r("./src/decorators/Predicate.ts"),a=r("./src/predicates/Predicate_FocusToDamage.ts"),i=r("./src/tasks/BTT_Success.ts"),c=r("./src/tasks/focus/BTT_SetFocalPoint.ts");t.BT_SetFocal=new s.Selector({nodes:[(0,o.IsSet)((0,c.BTT_SetFocalPoint)("target"),"canSeeTarget",!0,s.ObserverAborts.LowerPriority),(0,n.Predicate)((0,c.BTT_SetFocalPoint)("damageStimulusFocalPoint"),a.Predicate_FocusToDamage,!0,s.ObserverAborts.LowerPriority),(0,o.IsSet)((0,c.BTT_SetFocalPoint)("targetPredictedLocation"),"targetPredictedLocation",!0,s.ObserverAborts.LowerPriority),(0,o.IsSet)((0,c.BTT_SetFocalPoint)("targetLastKnownLocation"),"targetLastKnownLocation",!0,s.ObserverAborts.LowerPriority),i.BTT_Success]})},"./src/trees/BT_Strafe.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Strafe=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/tasks/environment/BTT_QuerySetArgument.ts"),n=r("./src/tasks/movement/BTT_MoveTo.ts"),a=r("./src/tasks/environment/BTT_RunEQSQuery.ts"),i=r("./src/tasks/BTT_SetValue.ts");t.BT_Strafe=new s.Sequence({nodes:[(0,o.BTT_QuerySetArgumentString)("strafe","TargetHash",(e=>e.target.hash)),(0,o.BTT_QuerySetArgumentFloat)("strafe","GridSize",(e=>8e3)),(0,o.BTT_QuerySetArgumentFloat)("strafe","SpaceBetween",(e=>1e3)),(0,a.BTT_RunEQSQuery)("strafe","strafeLocation"),(0,n.BTT_MoveTo)("strafeLocation"),(0,i.BTT_SetValue)((e=>e.strafeLocation=void 0))]})},"./src/trees/combat/BT_CanSeeTarget.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_CanSeeTarget=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/decorators/CanActivateAction.ts"),n=r("./src/decorators/Predicate.ts"),a=r("./src/helper.ts"),i=r("./src/tasks/BTT_SpecialAttack.ts"),c=r("./src/trees/combat/BT_CloseCombat.ts"),l=r("./src/trees/combat/BT_RangeCombat.ts");t.BT_CanSeeTarget=new s.Selector({nodes:[(0,o.CanActivateAction)((0,i.BTT_SpecialAttack)("targetLastKnownLocation"),"Action.SpecialAttack",!0,s.ObserverAborts.LowerPriority),(0,n.Predicate)(c.BT_CloseCombat,(e=>e.canMelee&&void 0!==e.targetLastKnownLocation&&(0,a.distanceToVec)(e.input.self.location,e.targetLastKnownLocation)<=4e3),!0,s.ObserverAborts.Both),l.BT_RangeCombat]})},"./src/trees/combat/BT_CloseCombat.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_CloseCombat=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/branches/ParallelBackground.ts"),n=r("./src/tasks/BTT_MeleeAttack.ts"),a=r("./src/tasks/movement/BTT_MoveTo.ts"),i=r("./src/tasks/BTT_Success.ts"),c=r("./src/trees/BT_SetFocal.ts");t.BT_CloseCombat=new o.ParallelBackground({nodes:[(0,n.BTT_MeleeAttack)("Weapon.Melee"),c.BT_SetFocal,new s.Selector({nodes:[(0,a.BTT_MoveTo)("targetLastKnownLocation",!0),i.BTT_Success]})]})},"./src/trees/combat/BT_Combat.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_Combat=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/decorators/IsSet.ts"),n=r("./src/decorators/Predicate.ts"),a=r("./src/trees/combat/BT_CanSeeTarget.ts"),i=r("./src/trees/BT_SearchTarget.ts"),c=r("./src/tasks/BTT_Success.ts"),l=r("./src/trees/BT_Patrol.ts"),u=r("./src/tasks/BTT_Taunt.ts"),d=r("./src/decorators/CanActivateAction.ts");t.BT_Combat=new s.Selector({nodes:[(0,o.IsSet)(a.BT_CanSeeTarget,"canSeeTarget",!0,s.ObserverAborts.Both),(0,d.CanActivateAction)((0,n.Predicate)(u.BTT_Taunt,(e=>!e.canSeeTarget)),"Action.Taunt"),(0,n.Predicate)(i.BT_SearchTarget,(e=>!e.canSeeTarget)),l.BT_Patrol,c.BTT_Success]})},"./src/trees/combat/BT_RangeCombat.ts":(e,t,r)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.BT_RangeCombat=void 0;const s=r("./node_modules/behaviortree/lib/index.js"),o=r("./src/branches/ParallelBackground.ts"),n=r("./src/tasks/movement/BTT_MoveTo.ts"),a=r("./src/tasks/BTT_Shoot.ts"),i=r("./src/tasks/BTT_Success.ts"),c=r("./src/trees/BT_SetFocal.ts"),l=r("./src/trees/BT_Strafe.ts");t.BT_RangeCombat=new o.ParallelBackground({nodes:[new s.Parallel({nodes:[(0,a.BTT_Shoot)("Weapon.Primary.LeftArm"),(0,a.BTT_Shoot)("Weapon.Primary.RightArm")]}),c.BT_SetFocal,new s.Selector({nodes:[(0,n.BTT_MoveTo)("targetLastKnownLocation"),l.BT_Strafe,i.BTT_Success]})]})},"./src/utils.ts":(e,t)=>{"use strict";Object.defineProperty(t,"__esModule",{value:!0}),t.IsWarMachine=t.IsVector=t.StringToEQSQueryType=void 0,t.StringToEQSQueryType=e=>{switch(e){case"away":return"away";case"cover":return"cover";case"hidden":return"hidden";case"patrol":return"patrol";case"strafe":return"strafe"}},t.IsVector=e=>"X"in e&&"Y"in e,t.IsWarMachine=e=>"hash"in e}},t={};!function r(s){var o=t[s];if(void 0!==o)return o.exports;var n=t[s]={exports:{}};return e[s](n,n.exports,r),n.exports}("./src/mech.ts")})();
//# sourceMappingURL=mech.js.map