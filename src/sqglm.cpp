#include "../sqglm.hpp"

namespace sqglm{

namespace detail{

template<typename T>struct sq_id{
	static HSQOBJECT id_;
};

template<typename T> HSQOBJECT sq_id<T>::id_;

template<typename T>
SQInteger clone(HSQUIRRELVM v){
	T *lhs;
	sq_getinstanceup(v,1,(SQUserPointer*)&lhs,&(sq_id<T>::id_) );
	T *rhs;
	sq_getinstanceup(v,2,(SQUserPointer*)&rhs,&(sq_id<T>::id_) );
	*lhs = *rhs;					
	return 0;
}

template<typename T>
SQInteger delete_instance(SQUserPointer p_ptr,SQInteger p_size){
		
	T *instance = reinterpret_cast<T*>(p_ptr);
	delete instance;
	return 0;
}

SQInteger register_member_func(HSQUIRRELVM& v,SQFUNCTION f,const char *fname,HSQOBJECT id)
{
	sq_pushobject(v,id);
	sq_pushstring(v,fname,-1);
	sq_newclosure(v,f,0);
	sq_newslot(v,-3,SQFalse);
	sq_pop(v,1);
}


SQInteger register_global_func(HSQUIRRELVM& v,SQFUNCTION f,const char *fname)
{
	sq_pushroottable(v);
	sq_pushstring(v,fname,-1);
	sq_newclosure(v,f,0);
	sq_newslot(v,-3,SQFalse);
	sq_pop(v,1);
}

template<typename T>
SQInteger constructor(HSQUIRRELVM v);


SQInteger with_assert_sq_getfloat(HSQUIRRELVM v,SQInteger nargs,float & val){
	SQInteger st_nargs = sq_gettop(v);
	if(st_nargs < nargs)
		return sq_throwerror(v, "too many args");
	if(sq_gettype(v,nargs) != OT_FLOAT)
		return sq_throwerror(v, "param is not float");
	sq_getfloat(v,nargs,&val);
	return 0;
}

template<>
SQInteger constructor<glm::vec2>(HSQUIRRELVM v){
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	SQFloat x,y;
	SQInteger error = 0;
	error = with_assert_sq_getfloat(v,2,x);if(error) return error;
	error = with_assert_sq_getfloat(v,3,y);if(error) return error;
	glm::vec2 * instance = new glm::vec2(x,y);
	sq_setinstanceup(v, 1, instance);
	sq_setreleasehook(v,1, delete_instance<glm::vec2>);
	return 0;
}

template<>
SQInteger constructor<glm::vec3>(HSQUIRRELVM v){
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	SQFloat x,y,z;
	SQInteger error = 0;
	error = with_assert_sq_getfloat(v,2,x);if(error) return error;
	error = with_assert_sq_getfloat(v,3,y);if(error) return error;
	error = with_assert_sq_getfloat(v,4,z);if(error) return error;
	glm::vec3 * instance = new glm::vec3(x,y,z);
	sq_setinstanceup(v, 1, instance);
	sq_setreleasehook(v,1, delete_instance<glm::vec3>);
	return 0;
}

template<>
SQInteger constructor<glm::vec4>(HSQUIRRELVM v){
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	SQFloat x,y,z,w;
	SQInteger error = 0;
	error = with_assert_sq_getfloat(v,2,x);if(error) return error;
	error = with_assert_sq_getfloat(v,3,y);if(error) return error;
	error = with_assert_sq_getfloat(v,4,z);if(error) return error;
	error = with_assert_sq_getfloat(v,5,w);if(error) return error;
	glm::vec4 * instance = new glm::vec4(x,y,z,w);
	sq_setinstanceup(v, 1, instance);
	sq_setreleasehook(v,1, delete_instance<glm::vec4>);
	return 0;
}

SQInteger setter_v2(HSQUIRRELVM v){
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	glm::vec2* obj;
	SQInteger error = 0;
	sq_getinstanceup(v,1,(SQUserPointer*)&obj,0);
	if(!strcmp(key, "x")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->x = val;
	}else if(!strcmp(key, "y")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->y = val;
	}else{
		return sq_throwerror(v, "invalid param");
	}
	return 0;
}

SQInteger setter_v3(HSQUIRRELVM v){
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	glm::vec3* obj;
	SQInteger error = 0;
	sq_getinstanceup(v,1,(SQUserPointer*)&obj,0);
	if(!strcmp(key, "x")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->x = val;
	}else if(!strcmp(key, "y")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->y = val;
	}else if(!strcmp(key, "z")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->z = val;
	}else{
		return sq_throwerror(v, "invalid param");
	}
	return 0;
}

SQInteger setter_v4(HSQUIRRELVM v){
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	glm::vec4* obj;
	SQInteger error = 0;
	sq_getinstanceup(v,1,(SQUserPointer*)&obj,0);
	if(!strcmp(key, "x")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->x = val;
	}else if(!strcmp(key, "y")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->y = val;
	}else if(!strcmp(key, "z")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->z = val;
	}else if(!strcmp(key, "w")){
		float val;error = with_assert_sq_getfloat(v,3,val);if(error) return error;
		obj->w = val;
	}else{
		return sq_throwerror(v, "invalid param");
	}
	return 0;
}

SQInteger getter_v2(HSQUIRRELVM v) {
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	glm::vec2* obj;
	SQInteger error = 0;
	sq_getinstanceup(v,1,(SQUserPointer*)&obj, 0);
	if(!strcmp(key, "x")){
		sq_pushfloat(v,obj->x);
	}else if(!strcmp(key, "y")){
		sq_pushfloat(v,obj->y);
	}else{
		return sq_throwerror(v, "invalid param");
	}
	return 1;
}

SQInteger getter_v3(HSQUIRRELVM v) {
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	glm::vec3* obj;
	SQInteger error = 0;
	sq_getinstanceup(v,1,(SQUserPointer*)&obj, 0);
	if(!strcmp(key, "x")){
		sq_pushfloat(v,obj->x);
	}else if(!strcmp(key, "y")){
		sq_pushfloat(v,obj->y);
	}else if(!strcmp(key, "z")){
		sq_pushfloat(v,obj->z);
	}else{
		return sq_throwerror(v, "invalid param");
	}
	return 1;
}

SQInteger getter_v4(HSQUIRRELVM v) {
	SQChar const * key; sq_getstring(v,2,(SQChar const**)&key);
	glm::vec4* obj;
	SQInteger error = 0;
	sq_getinstanceup(v,1,(SQUserPointer*)&obj, 0);
	if(!strcmp(key, "x")){
		sq_pushfloat(v,obj->x);
	}else if(!strcmp(key, "y")){
		sq_pushfloat(v,obj->y);
	}else if(!strcmp(key, "z")){
		sq_pushfloat(v,obj->z);
	}else if(!strcmp(key, "w")){
		sq_pushfloat(v,obj->w);
	}else{
		return sq_throwerror(v, "invalid param");
	}
	return 1;
}
// +++++++++++++++++++op
template<typename T>
SQInteger add_v(HSQUIRRELVM v) {
	SQChar const * buff; sq_getstring(v,2,(SQChar const**)&buff);
	T* lhs;
	sq_getinstanceup(v,1,(SQUserPointer*)&lhs, 0);
	T* rhs;
	sq_getinstanceup(v,2,(SQUserPointer*)&rhs, 0);
	T * instance = new T(*lhs + *rhs);
	sq_setinstanceup(v, 2, instance);
	sq_setreleasehook(v,2, delete_instance<T>);
	return 1;
}

template<typename T>
SQInteger sub_v(HSQUIRRELVM v) {
	SQChar const * buff; sq_getstring(v,2,(SQChar const**)&buff);
	T* lhs;
	sq_getinstanceup(v,1,(SQUserPointer*)&lhs, 0);
	T* rhs;
	sq_getinstanceup(v,2,(SQUserPointer*)&rhs, 0);
	T * instance = new T(*lhs - *rhs);
	sq_setinstanceup(v, 2, instance);
	sq_setreleasehook(v,2, delete_instance<T>);
	return 1;
}

template<typename T>
SQInteger mul_v(HSQUIRRELVM v) {
	SQChar const * buff; sq_getstring(v,2,(SQChar const**)&buff);
	T* lhs;
	sq_getinstanceup(v,1,(SQUserPointer*)&lhs, 0);
	T* rhs;
	sq_getinstanceup(v,2,(SQUserPointer*)&rhs, 0);
	T * instance = new T(*lhs * *rhs);
	sq_setinstanceup(v, 2, instance);
	sq_setreleasehook(v,2, delete_instance<T>);
	return 1;
}

template<typename T>
SQInteger div_v(HSQUIRRELVM v) {
	SQChar const * buff; sq_getstring(v,2,(SQChar const**)&buff);
	T* lhs;
	sq_getinstanceup(v,1,(SQUserPointer*)&lhs, 0);
	T* rhs;
	sq_getinstanceup(v,2,(SQUserPointer*)&rhs, 0);
	T * instance = new T(*lhs / *rhs);
	sq_setinstanceup(v, 2, instance);
	sq_setreleasehook(v,2, delete_instance<T>);
	return 1;
}
// -------------------op

// +++++++++++++++++++func
template<typename T>
SQInteger dot(HSQUIRRELVM v){
	T * lhs,* rhs;
	sq_getinstanceup(v,2,(SQUserPointer*)&lhs, 0);
	sq_getinstanceup(v,3,(SQUserPointer*)&rhs, 0);
	sq_pushfloat(v,glm::dot(*lhs,*rhs));
	return 1;
}

template<typename T>
SQInteger cross(HSQUIRRELVM v){
	T * lhs,* rhs;
	sq_getinstanceup(v,2,(SQUserPointer*)&lhs, 0);
	sq_getinstanceup(v,3,(SQUserPointer*)&rhs, 0);
	T * instance = new T( glm::cross(*lhs,*rhs) );
	sq_setinstanceup(v, 3, instance);
	sq_setreleasehook(v,3, delete_instance<T>);
	return 1;
}
// -------------------func

template<typename T>
HSQOBJECT class_init(HSQUIRRELVM v,SQFUNCTION c,const SQChar * p_name)
{	
	HSQOBJECT class_id;
	sq_pushroottable(v);
	sq_pushstring(v,p_name,-1);

	sq_newclass(v,SQFalse);
	sq_getstackobj(v,-1,&class_id);		
	sq_settypetag(v,-1,&class_id);		

	HSQOBJECT string_constructor;
	sq_pushstring(v,_SC("constructor"),-1);
	sq_resetobject(&string_constructor);
	sq_getstackobj(v,-1,&string_constructor);
	sq_newclosure(v,c,0);
	sq_newslot(v,-3,false);
		
	sq_pushstring(v,_SC("_cloned"),-1);
	sq_newclosure(v,clone<T>,0);
	sq_newslot(v,-3,false);
		
	sq_newslot(v,-3,false);
	sq_pop(v,1);

	return class_id;
}

}//--detail

bool bind_sqglm(HSQUIRRELVM v){
	namespace d = detail;
	d::sq_id<glm::vec2>::id_ = d::class_init<glm::vec2>(v,d::constructor<glm::vec2>,_SC("Vec2"));
	d::register_member_func(v,d::setter_v2,_SC("_set"),d::sq_id<glm::vec2>::id_);
	d::register_member_func(v,d::getter_v2,_SC("_get"),d::sq_id<glm::vec2>::id_);
	d::register_member_func(v,d::add_v<glm::vec2>,_SC("_add"),d::sq_id<glm::vec2>::id_);
	d::register_member_func(v,d::sub_v<glm::vec2>,_SC("_sub"),d::sq_id<glm::vec2>::id_);
	d::register_member_func(v,d::mul_v<glm::vec2>,_SC("_mul"),d::sq_id<glm::vec2>::id_);
	d::register_member_func(v,d::div_v<glm::vec2>,_SC("_div"),d::sq_id<glm::vec2>::id_);
	d::sq_id<glm::vec3>::id_ = d::class_init<glm::vec3>(v,d::constructor<glm::vec3>,_SC("Vec3"));
	d::register_member_func(v,d::setter_v3,_SC("_set"),d::sq_id<glm::vec3>::id_);
	d::register_member_func(v,d::getter_v3,_SC("_get"),d::sq_id<glm::vec3>::id_);
	d::register_member_func(v,d::add_v<glm::vec3>,_SC("_add"),d::sq_id<glm::vec3>::id_);
	d::register_member_func(v,d::sub_v<glm::vec3>,_SC("_sub"),d::sq_id<glm::vec3>::id_);
	d::register_member_func(v,d::mul_v<glm::vec3>,_SC("_mul"),d::sq_id<glm::vec3>::id_);
	d::register_member_func(v,d::div_v<glm::vec3>,_SC("_div"),d::sq_id<glm::vec3>::id_);
	d::sq_id<glm::vec4>::id_ = d::class_init<glm::vec4>(v,d::constructor<glm::vec4>,_SC("Vec4"));
	d::register_member_func(v,d::setter_v4,_SC("_set"),d::sq_id<glm::vec4>::id_);
	d::register_member_func(v,d::getter_v4,_SC("_get"),d::sq_id<glm::vec4>::id_);
	d::register_member_func(v,d::add_v<glm::vec4>,_SC("_add"),d::sq_id<glm::vec4>::id_);
	d::register_member_func(v,d::sub_v<glm::vec4>,_SC("_sub"),d::sq_id<glm::vec4>::id_);
	d::register_member_func(v,d::mul_v<glm::vec4>,_SC("_mul"),d::sq_id<glm::vec4>::id_);
	d::register_member_func(v,d::div_v<glm::vec4>,_SC("_div"),d::sq_id<glm::vec4>::id_);

	d::register_global_func(v,d::dot<glm::vec2>,_SC("Dot2"));
	d::register_global_func(v,d::dot<glm::vec3>,_SC("Dot3"));
	d::register_global_func(v,d::dot<glm::vec3>,_SC("Dot4"));

	d::register_global_func(v,d::cross<glm::vec3>,_SC("Cross"));

	return true;
}

}//--sqglm
