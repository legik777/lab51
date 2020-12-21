// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <boostf.hpp>
    std::vector<Broker> Broker::brokerVector;
TEST(file, searchtest) {
    std::string path_to_ftp = "../";
    std::vector<std::string> vec;
    vec = recdir(path_to_ftp);
    std::cout << "number of files found " + vec.back() << std::endl;
    if (boost::filesystem::exists(path_to_ftp)) {
        std::cout << path_to_ftp << std::endl;
        EXPECT_EQ(422,  std::stoi(vec.back()));
        vec.pop_back();
    } else {
        std::cout << "dir not exist" << std::endl;
    }
  EXPECT_TRUE(true);
}
TEST(file, searchtest2) {
    Broker::clearVector();
    bool test2 = true;
    std::vector<std::string> vect = {
 "1broker:ib account:00100001 files:48 lastdate:20181018",
"1broker:ib account:00100002 files:48 lastdate:20181018",
"1broker:ib account:00100003 files:47 lastdate:20181017",
"1broker:bcs account:00122223 files:46 lastdate:20181016",
"1broker:bcs account:00123456 files:44 lastdate:20181014",
"1broker:bcs account:00123458 files:48 lastdate:20181018",
"1broker:bcs account:00143456 files:46 lastdate:20181016",
"1broker:otkritie account:03934520 files:48 lastdate:20181018",
"1broker:otkritie account:03934523 files:47 lastdate:20181017"};
    std::string path_to_ftp = "../";
    if (boost::filesystem::exists(path_to_ftp)) {
        std::cout << path_to_ftp << std::endl;
        recdir(path_to_ftp);
        std::vector<Broker> vec = Broker::ListBrokersv();
        int lvec = vect.size();
        for (int i = 0; i < lvec; i++) {
            if (vect[i] != vec[i].toString()) {
                std::cout  << std::endl
                    << vec[i].toString() << std::endl << std::endl;
                test2 = false;
                //break; << vect[i]
        }
        }
        EXPECT_EQ(test2, 1);
    } else {
        std::cout << "dir not exist" << std::endl;
    }
    EXPECT_TRUE(true);
}
