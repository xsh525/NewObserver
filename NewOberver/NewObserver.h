//Copyright(C) 2015 xsh525@sina.com
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sub license, and / or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.
#ifndef _NEWOBSERVER_H
#define _NEWOBSERVER_H

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

#define PARA_TYPE wstring

#define REGISTER_ACTION(event_name, action_id, class_name, point_obj_name, point_fun, para) \
new Functor<class_name> (event_name, action_id, point_obj_name, &##class_name::##point_fun, para)

#define UNREGISTER_ACTION(action_id) unregisterFunction(action_id)
#define UNREGISTER_EVENT(event_name) unregisterEvent(event_name)
#define INVOKE_EVENT(event_name) invoke(event_name)

class FunctorBase;
typedef multimap<wstring, FunctorBase*> EVENT_MAP;
extern EVENT_MAP event_mapping;

class FunctorBase
{
public:
    virtual void operator()() = 0;
    virtual ~FunctorBase() {};
    int m_id;
};

template<class T>
class Functor :public FunctorBase
{
    typedef void (T::*Func)(const PARA_TYPE&);

public:
    Functor(const wstring& event_name, const int action_id, T& rt, const Func pf, const PARA_TYPE& para)
        :t(rt), m_func(pf), m_para(para)
    {
        m_id = action_id;
        //Construct the event mapping
        event_mapping.emplace(pair<const wstring, FunctorBase*>(event_name, this));
    }

    virtual void operator()()
    {
        (t.*m_func)(m_para);
    }

private:
    PARA_TYPE m_para;
    T& t;
    Func m_func;
};

inline void unregisterFunction(int id)
{
    for (auto iter = event_mapping.begin(); iter != event_mapping.end(); ++iter)
    {
        if (id == (*iter).second->m_id)
        {
            delete (*iter).second;
            event_mapping.erase(iter);
            return;
        }
    }
}

inline void unregisterEvent(const wstring& event_name)
{
    auto pos = event_mapping.equal_range(event_name);
    for_each(pos.first, pos.second, [](decltype(*pos.first) func) {delete func.second;});
    event_mapping.erase(pos.first, pos.second);
}

inline void invoke(wstring event_name)
{
    auto pos = event_mapping.equal_range(event_name);
    for_each(pos.first, pos.second, [](decltype(*pos.first) func) {(*(func).second)();});
}

#endif //_NEWOBSERVER_H