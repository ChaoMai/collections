#include <cassert>
#include <iostream>
#include <string>
#include "leveldb/db.h"

using namespace std;

// class TwoPartComparator : public leveldb::Comparator {
//    public:
//     int Compare(const leveldb::Slice &a, const leveldb::Slice &b) const {
//         int a1, a2, b1, b2;
//         ParseKey(a, &a1, &a2);
//         ParseKey(b, &b1, &b2);
//         if (a1 < b1) return -1;
//         if (a1 > b1) return +1;
//         if (a2 < b2) return -1;
//         if (a2 > b2) return +1;
//         return 0;
//     }

//     const char *Name() const { return "TwoPartComparator"; }
//     void FindShortestSeparator(std::string *, const leveldb::Slice &) const
//     {} void FindShortSuccessor(std::string *) const {}
// };

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
    cout << "itertor" << endl;
    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());

    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        cout << it->key().ToString() << " " << it->value().ToString() << endl;
    }
    assert(it->status().ok());

    delete it;

    // snapshot
    cout << "snapshot" << endl;
    leveldb::ReadOptions read_snap_opts;
    read_snap_opts.snapshot = db->GetSnapshot();
    leveldb::Iterator *snap_it = db->NewIterator(read_snap_opts);

    cout << "delete key2" << endl;
    status = db->Delete(leveldb::WriteOptions(), key2);
    assert(status.ok());

    for (snap_it->SeekToFirst(); snap_it->Valid(); snap_it->Next()) {
        cout << snap_it->key().ToString() << " " << snap_it->value().ToString()
             << endl;
    }
    assert(snap_it->status().ok());

    delete snap_it;
    db->ReleaseSnapshot(read_snap_opts.snapshot);

    delete db;
}
