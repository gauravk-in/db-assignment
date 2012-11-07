#!/bin/sh

echo "Loading the generated code to FakeDB"

cp gen_code/schema.h ../fakedb/include/schema.h
cp gen_code/storage.h ../fakedb/include/storage.h
cp gen_code/schema_constructors.cpp ../fakedb/schema_constructors.cpp
cp gen_code/storage.cpp ../fakedb/storage.cpp
