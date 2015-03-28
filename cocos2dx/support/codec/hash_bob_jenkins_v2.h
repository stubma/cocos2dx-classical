/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-classical
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef __hash_bob_jenkins_v2__
#define __hash_bob_jenkins_v2__

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t hashword(const uint32_t *k, size_t length, uint32_t initval);
extern uint32_t hashbig( const void *key, size_t length, uint32_t initval);
extern uint32_t hashlittle( const void *key, size_t length, uint32_t initval);
extern void hashlittle2(const void *key, size_t length, uint32_t *pc, uint32_t *pb);
extern uint32_t hashword(const uint32_t *k, size_t length, uint32_t initval);
extern void hashword2(const uint32_t *k, size_t length, uint32_t *pc, uint32_t *pb);
    
#ifdef __cplusplus
}
#endif

#endif // #ifndef __hash_bob_jenkins_v2__