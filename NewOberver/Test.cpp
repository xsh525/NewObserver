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

#include "stdafx.h"
#include "NewObserver.h"
#include <iostream>

class Cat
{
public:
    Cat(wstring name) :m_name(name) {};

    void cry(const PARA_TYPE& para)
    {
        wcout << L"Cat " << m_name << L" is crying! " << para << endl;
    }

    void sleep(const PARA_TYPE& para)
    {
        wcout << L"Cat " << m_name << L" is sleeping! " << para << endl;
    }

private:
    wstring m_name;
};

class Plane
{
public:
    Plane(wstring name) :m_name(name) {};

    void run(const PARA_TYPE& para)
    {
        wcout << L"Plane " << m_name << L" is running! " << para << endl;
    }

    void fly(const PARA_TYPE& para)
    {
        wcout << L"Plane " << m_name << L" is flying! " << para << endl;
    }

private:
    wstring m_name;
};

class Switch
{
public:
    Switch(wstring name) :m_name(name) {};

    void on(const PARA_TYPE& para)
    {
        wcout << L"Switch " << m_name << L" is on! " << para << endl;
    }

    void off(const PARA_TYPE& para)
    {
        wcout << L"Switch " << m_name << L" is off! " << para << endl;
    }

private:
    wstring m_name;
};

EVENT_MAP event_mapping;

Cat cat1(L"Amy");
Cat cat2(L"Ivy");
Plane plane1(L"blackhawk");
Plane plane2(L"rainbow");
Switch switch1(L"electronic");
Switch switch2(L"water");

int _tmain(int argc, TCHAR *argv[])
{
    //RegisterAction(Action Name, Action Unique ID, Class Name, Object Name, Member Function Name, Parameter[String])
    REGISTER_ACTION(L"Event1", 1, Cat, cat1, cry, L"wwWW");
    REGISTER_ACTION(L"Event1", 2, Cat, cat2, sleep, L"zzZZ");
    REGISTER_ACTION(L"Event1", 3, Switch, switch1, on, L"^^^^^");
    REGISTER_ACTION(L"Event1", 4, Plane, plane2, fly, L"..--``");
    REGISTER_ACTION(L"Event1", 5, Switch, switch2, off, L"-----");

    REGISTER_ACTION(L"Event2", 6, Plane, plane1, run, L"......");
    REGISTER_ACTION(L"Event2", 7, Cat, cat2, sleep, L"zZ");
    REGISTER_ACTION(L"Event2", 8, Switch, switch2, off, L"-------");
    REGISTER_ACTION(L"Event2", 9, Plane, plane2, run, L"....");
    REGISTER_ACTION(L"Event2", 10, Cat, cat1, cry, L"wW");
    REGISTER_ACTION(L"Event2", 11, Cat, cat1, cry, L"wwWW");
    REGISTER_ACTION(L"Event2", 12, Cat, cat1, cry, L"wwwWWW");

    wcout << L"###########Begin Test Event1###########" << endl;
    INVOKE_EVENT(L"Event1");
    wcout << L"###########End Test Event1###########" << endl << endl;

    wcout << L"###########Begin Test Event2###########" << endl;
    INVOKE_EVENT(L"Event2");
    wcout << L"###########End Test Event2###########" << endl << endl;

    wcout << L"###########Begin Test UnregisterAction###########" << endl;
    UNREGISTER_ACTION(4);
    UNREGISTER_ACTION(1);
    UNREGISTER_ACTION(-1);
    INVOKE_EVENT(L"Event1");
    wcout << L"###########End Test UnregisterAction###########" << endl << endl;

    wcout << L"###########Begin Test UnregisterEvent###########" << endl;
    UNREGISTER_EVENT(L"Event2");
    UNREGISTER_EVENT(L"Event-1");
    INVOKE_EVENT(L"Event2");
    wcout << L"###########End Test UnregisterEvent###########" << endl << endl;

    system("PAUSE");
    return EXIT_SUCCESS;
}