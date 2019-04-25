const state = require('./Global').state;
const Collider = require('./Collider');
const Widget = require('./Widget');
let Utils = require('./Utils');
const fs = require('fs');

const Utils2 = require('../Utils');


class Node {

    static get_node_components(node) {
        if ('_components' in node) {
            let idxs = node._components;
            let components = [];
            idxs.forEach( idx => {
                let idx_num = idx.__id__;
                components.push(state._json_data[idx_num]);
            });
            return components;
        }
        return null;
    }

    static get_node_component_of_type(node, t) {
        let components = Node.get_node_components(node);
        if (components != null) {
            for (let i = 0, len = components.length; i < len; ++i) {
                let c = components[i];
                if (c.__type__ === t)
                    return c;
            }
        }
        return null;
    }

    static get_node_components_of_type(node, t) {
        let components = Node.get_node_components(node);

        let result = [];
        if (components != null) {
            for (let i = 0, len = components.length; i < len; ++i) {
                let c = components[i];
                if (c.__type__ === t)
                    result.push(c);
            }
        }

        return result;
    }

    static guess_type_from_components(components) {
        // ScrollView, Button & ProgressBar should be before Sprite
        let supported_components = ['cc.Button', 'cc.ProgressBar', 'cc.ScrollView', 'cc.Layout',
            'cc.EditBox', 'cc.Label', 'sp.Skeleton', 'cc.Sprite',
            'cc.ParticleSystem', 'cc.TiledMap', 'cc.Canvas', 'cc.RichText',
            'cc.VideoPlayer', 'cc.WebView', 'cc.Slider', 'cc.Toggle', 'cc.ToggleGroup',
            'cc.PageView', 'cc.Mask', 'dragonBones.ArmatureDisplay'];
    
        if (!components)
            return 'cc.Node';
    
        let node_components = components.map(x => x.__type__);
        // special case for object without components
        if (node_components.length == 0)
            return 'cc.Node';
    
        for (let i = 0, len = supported_components.length; i < len; ++i) {
            let supported = supported_components[i];
            if (node_components.includes(supported)) {
                Utils.log('Choose ' + supported + ' from ' + node_components);
                return supported;
            }
        }
        Utils.log('Unknown components ' + node_components);
        Utils.log('treat all unknown components as cc.Node')
        return 'cc.Node';
    }
    
    static guess_type(node_data) {
        let components = Node.get_node_components(node_data);
        if (components)
            return Node.guess_type_from_components(components);
    
        // prefab don't have componets, should guess type from prefab node data
        if (node_data._prefab)
            return 'cc.Prefab';
    
        return null;
    }

    constructor(data) {
        this._node_data = data;
        this._children = [];
        this._jsonNode = {
            object: null,
            object_type: 'Node',
            children: []
        }
        this._properties = {};
    }

    add_property_str(newkey, value, data) {
        if (value in data) {
            let new_value = data[value];
            this._properties[newkey] = new_value;
        }
    }

    add_property_size(newkey, value, data) {
        if (value in data) {
            let w = data[value].width;
            let h = data[value].height;
            this._properties[newkey] = {w:w, h:h};
        }
    }

    add_property_int_width_floor(newkey, value, data) {
        if (value in data) {
            let i = Math.floor(data[value]);
            this._properties[newkey] = i;
        }
    }


    add_property_int(newkey, value, data) {
        if (value in data) {
           //let i = Math.floor(data[value]);
            this._properties[newkey] = data[value];
        }
    }

    add_property_vec2(newkey, value, data) {
        if (value in data) {
            let x = data[value].x;
            let y = data[value].y;
            this._properties[newkey] = {x:x, y:y};
        }
    }

    add_property_rgb(newkey, value, data) {
        if (value in data) {
            let r = data[value].r;
            let g = data[value].g;
            let b = data[value].b;
            this._properties[newkey] = {r:parseInt(r), g:parseInt(g), b:parseInt(b)};
        }
    }

    add_property_rgba(newkey, value, data) {
        if (value in data) {
            let r = data[value].r;
            let g = data[value].g;
            let b = data[value].b;
            let a = data[value].a;
            this._properties[newkey] = {r:parseInt(r), g:parseInt(g), b:parseInt(b),a:parseInt(a)};
        }
    }

    add_property_bool(newkey, value, data) {
        if (value in data)
            this._properties[newkey] = data[value];
    }

    get_class_name() {
        return this.constructor.name;
    }

    parse_properties() {
        // 1st: parse self
        this.parse_node_properties();
        
        // 2nd: parse children
        this.parse_children();
    }

    /** A Node may have `cc.Sprite` and `cc.MotionStreak` components, and a Node's
     * type is determined by its component. Then what is the type of the Node? To
     * resolve the issue, we handle `cc.MotionStreak` component here.
     */
    handle_motion_streak(father) {
        if (Node.get_node_component_of_type(this._node_data, 'cc.MotionStreak') != null) {
            let n = Utils.create_node('cc.MotionStreak', this._node_data);
            father.add_child(n);
        }
    }

    parse_children() {
        if (this._node_data._children)
            this._node_data._children.forEach(function(item) {
                this.parse_child(item.__id__);
            }.bind(this));
    }

    parse_node_properties() {
        let data = this._node_data;
        this.add_property_size('contentSize', '_contentSize', data);
        this.add_property_bool('enabled', '_active', data);
        this.add_property_str('name', '_name', data);
        this.add_property_vec2('anchorPoint', '_anchorPoint', data);
        this.add_property_bool('cascadeOpacityEnabled', '_cascadeOpacityEnabled', data);
        this.add_property_rgb('color', '_color', data);
        this.add_property_int('globalZOrder', '_globalZOrder', data);
        this.add_property_int('localZOrder', '_localZOrder', data);
        this.add_property_int_width_floor('opacity', '_opacity', data);
        this.add_property_bool('opacityModifyRGB', '_opacityModifyRGB', data);
        this.add_property_vec2('position', '_position', data);
        this.add_property_int('rotationSkewX', '_rotationX', data);
        this.add_property_int('rotationSkewY', '_rotationY', data);

        if(data._scale)
        {
            this.add_property_int('scaleX', 'x', data._scale);
            this.add_property_int('scaleY', 'y', data._scale);
        }   
        else
        {
            this.add_property_int('scaleX', '_scaleX', data);
            this.add_property_int('scaleY', '_scaleY', data);
        }
        

        this.add_property_int('skewX', '_skewX', data);
        this.add_property_int('skewY', '_skewY', data);
        this.add_property_int('tag', '_tag', data);
        this.add_property_int('groupIndex', 'groupIndex', data);

        this.parse_clip();
        this.parse_colliders();
        this.parse_widget();
    }

    parse_child(node_idx) {
        let node = state._json_data[node_idx];
        if (node.__type__ === 'cc.Node') {
            let node_type = Node.guess_type(node);
            if (node_type != null) {
                let n = Utils.create_node(node_type, node);
                this.adjust_child_parameters(n);
                if (n != null) {
                    this.add_child(n);
                    n.handle_motion_streak(this);
                }
            }
        }
    }

    parse_colliders() {
        let collider_components = Node.get_node_components_of_type(this._node_data, 'cc.BoxCollider');
        collider_components =  collider_components.concat(Node.get_node_components_of_type(this._node_data, 'cc.CircleCollider'));
        collider_components = collider_components.concat(Node.get_node_components_of_type(this._node_data, 'cc.PolygonCollider'));

        this._properties.colliders = [];
        for (let i = 0, len = collider_components.length; i < len; ++i) {
            let collider_component = collider_components[i];
            let collider_info = Collider.parse(collider_component);
            this._properties.colliders.push(collider_info);
        }
    }

    parse_widget() {
        let component = Node.get_node_components_of_type(this._node_data, 'cc.Widget');
        if(component.length === 1) {
            this._properties.widget = Widget.parse(component[0]);
        }
    }

    parse_clip() {
        let component = Node.get_node_component_of_type(this._node_data, 'cc.Animation');
        if (component) {
            let anim = {
                playOnLoad: component.playOnLoad,
                clips: []
            };

            function parseCurveDataProps(props) {
                // curve property may
                // - doesn't exist
                // - string
                // - an array of data
                function parseCurveProperty(from, to) {
                    let curve = from.curve;
                    if (curve) {
                        let curve_type = typeof(curve);
                        if (curve_type === 'string')
                            to.curveType = curve;
                        else {
                            // array of data
                            to.curveData = curve.slice();
                        }
                    }
                }

                function addProp(from, from_key, to, to_key) {
                    if (from[from_key]) {
                        to[to_key] = [];
                        from[from_key].forEach(function(prop) {
                            let value = {
                                frame: prop.frame,
                                value: prop.value,
                            };

                            parseCurveProperty(prop, value);
                            to[to_key].push(value);
                        });
                    }
                }

                let result = {};
                addProp(props, 'rotation', result, 'rotation');
                addProp(props, 'x', result, 'positionX');
                addProp(props, 'y', result, 'positionY');
                addProp(props, 'anchorX', result, 'anchorX');
                addProp(props, 'anchorY', result, 'anchorY');
                addProp(props, 'scaleX', result, 'scaleX');
                addProp(props, 'scaleY', result, 'scaleY');
                addProp(props, 'skewX', result, 'skewX');
                addProp(props, 'skewY', result, 'skewY');
                addProp(props, 'opacity', result, 'opacity');
                addProp(props, 'height', result, 'height');
                addProp(props, 'width', result, 'width');
                

                //cc.Sprite.spriteFrame
                if (props['cc.Sprite']) {
                    result['spriteFrame'] = [];
                    //addProp(props, 'cc.Sprite',  result, 'cc.Sprite');
                    props['cc.Sprite'].spriteFrame.forEach(function(sprite){

                         try{
                            let path = Utils.get_sprite_frame_name_by_uuid(sprite.value.__uuid__);
                           // path = 'creator/'+path;
                            let value = {
                                frame: sprite.frame,
                                value: path
                            };
                            parseCurveProperty(sprite, value);
                            result['spriteFrame'].push(value);
                        }catch(e)
                        {
                            Utils2.log("spriteFrame not find "+sprite.value.__uuid__)
                        }

                    });
                }

                // position -> {x:, y:, curveType?, curveData?}
                if (props.position) {
                    result.position = [];
                    props.position.forEach(function(pos) {
                        let value = {
                            frame: pos.frame,
                            value: {x: pos.value[0], y: pos.value[1]}
                        };
                        parseCurveProperty(pos, value);
                        result.position.push(value);
                    });
                }

                //scale
                if (props.scale) {
                    result['scaleX'] = [];
                    result['scaleY'] = [];

                     props.scale.forEach(function(scl) {
                        let valueX = {
                            frame: scl.frame,
                            value: scl.value['x']
                        };
                        parseCurveProperty(scl, valueX);
                        result['scaleX'].push(valueX)


                        let valueY = {
                            frame: scl.frame,
                            value: scl.value['y']
                        };
                        parseCurveProperty(scl, valueY);
                        result['scaleY'].push(valueY)
                    });
                }

                // color
                if (props.color) {
                    result.color = [];
                    props.color.forEach(function(clr){
                        let value = {
                            frame: clr.frame,
                            value: {r:clr.value.r, g:clr.value.g, b:clr.value.g, a:clr.value.a}
                        };
                        parseCurveProperty(clr, value);
                        result.color.push(value);
                    });
                }

                return result;
            }

            component._clips.forEach(function(clip) {
                let clip_uuid = clip.__uuid__;
                if (clip_uuid in state._clips)
                {
                    anim.clips.push(state._clips[clip_uuid]);
                }
                else
                {
                    let clip_content = JSON.parse(fs.readFileSync(Utils.get_file_by_uuid(clip_uuid)));//uuidinfos[clip_uuid]));
                    
                    // parse curveData
                    let animationClip = {
                        name: clip_content._name,
                        duration: clip_content._duration,
                        sample: clip_content.sample,
                        speed: clip_content.speed,
                        wrapMode: clip_content.wrapMode,
                        curveData: []
                    };

                    let curveData = clip_content.curveData;
                    if (curveData.paths)
                    {
                        // animationclip of sub nodes
                        for(let path in curveData.paths) {
                            if (curveData.paths.hasOwnProperty(path) && curveData.paths[path].props) {
                                // how to support comps?
                                let subAnim = {
                                    path: path,
                                    props: parseCurveDataProps(curveData.paths[path].props)
                                };
                                animationClip.curveData.push(subAnim);
                            }
                            
                            if (curveData.paths.hasOwnProperty(path) && curveData.paths[path].comps) {
                                let subAnim = {
                                    path: path,
                                    props: parseCurveDataProps(curveData.paths[path].comps)
                                };
                                animationClip.curveData.push(subAnim);
                            }
                        }
                    }
                    else if(curveData.comps)
                    {
                        let subAnim = {
                                    path: "",
                                    props: parseCurveDataProps(curveData.comps)
                                };
                        animationClip.curveData.push(subAnim);
                    }

                    // parse self animationclip
                    if (curveData.props)
                        animationClip.curveData.push({props: parseCurveDataProps(curveData.props)}); 

                    anim.clips.push(animationClip);
                    state._clips[clip_uuid] = animationClip;
                }
            });
            // default clip
            if (component._defaultClip)
                anim.defaultClip = state._clips[component._defaultClip.__uuid__].name;

            this._properties.anim = anim;
        }
    }

    add_child(node) {
        this._children.push(node);
    }

    print_scene_graph(tab) {
        // TODO
    }

    get_description(tab) {
        return ('-' * tab + this.get_class_name);
    }

    /**
     * JSON stuff
     */
    to_json(depth, sibling_idx) {
        this.to_json_begin(depth, sibling_idx);
        this.to_json_properties();

        for (let idx = 0, len = this._children.length; idx < len; ++idx) {
            let child = this._children[idx];
            let jsonChild = child.to_json(depth + 1, idx);
            if (jsonChild != null)
                this._jsonNode.children.push(jsonChild);
        }

        return this._jsonNode;
    }

    to_json_begin(depth, sibling_idx) {

    }

    to_json_properties() {
        this._jsonNode.object = this._properties;
    }

    adjust_child_parameters(child) {
        // Only useful when a parent wants to override some child parameter
        // As an example, ScrollView needs to adjust its children position
    }
}

module.exports = Node;
