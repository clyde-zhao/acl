//
// Created by shuxin ����zheng on 2023/7/27.
//

#pragma once

#include "db/db.h"

#ifdef HAS_WT

typedef struct __wt_connection WT_CONNECTION;

namespace pkv {

class wt_sess;

class wdb : public db {
public:
    explicit wdb(size_t cache_max = 10000);
    ~wdb() override;

protected:
    // @override
    bool open(const char* path) override;

    // @override
    bool set(const std::string& key, const std::string& value) override;

    // @override
    bool get(const std::string& key, std::string& value) override;

    // @override
    bool del(const std::string& key) override;

public:
    WT_CONNECTION* get_db() const {
        return db_;
    }

private:
    std::string path_;
    WT_CONNECTION *db_;

    std::vector<wt_sess*> sessions_;
    size_t cache_max_;

    wt_sess* get_session();
    void put_session(wt_sess* sess);
};

} // namespace pkv

#endif // HAS_WT