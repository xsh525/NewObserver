This is a C++ implementaion of oberver-like pattern. But with several significant differences:
1. Register at single point.
2. Clients do not have to be derived from same base class.
3. Use string to stand for events, so it easy to read events from outside.
4. Member functions(with same prototype) from different places can be registered as listener.
5. Same member function can be registered multitimes.

Built by Visual Studio 2013 and tested on Windows 7 x64.

Author: Xu Shihong
Mail: xsh525@sina.com
