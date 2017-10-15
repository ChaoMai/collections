#include <cassert>
#include <iostream>
#include <string>
#include "leveldb/db.h"

using namespace std;

int main() {
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);
    assert(status.ok());

    // write
    string key1 = "k1";
    string value1 = "hello, world";
    status = db->Put(leveldb::WriteOptions(), key1, value1);
    assert(status.ok());

    string key2 = "k2";
    status = db->Put(leveldb::WriteOptions(), key2, value1);
    assert(status.ok());

    string key3 = "k3";
    status = db->Put(leveldb::WriteOptions(), key3, value1);
    assert(status.ok());

    // read
    string value2;
    status = db->Get(leveldb::ReadOptions(), key1, &value2);
    assert(status.ok());
    assert(value1 == value2);

    status = db->Delete(leveldb::WriteOptions(), key1);
    assert(status.ok());

    // iterator
    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());

    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        cout << it->key().ToString() << " " << it->value().ToString() << endl;
    }
    assert(it->status().ok());

    // snapshot

    delete db;
}
