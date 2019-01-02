#ifndef GUARD_H_
#define GUARD_H_

namespace bigpipe {
template <typename LockType>
class Guard {
public:
    /* Guard 构造函数，对Mutex加锁*/
    Guard(LockType* lock) : _locked(false), _lock(lock) {
        if (NULL != _lock) {
            if (0 == _lock->lock()) {
                _locked = true;
            }
        }
    }

    /* 检测加锁是否成功 */
    bool is_locked() const {
        return _locked;
    }

    /* 析构函数，对Mutex解锁 */
    ~Guard() {
        if (NULL != _lock) {
            if (0 == _lock->unlock()) {
                _locked = false;
            }
        }
    }
private:
    volatile bool _locked;
    LockType* _lock;
};
}
#endif //GUARD_H_
