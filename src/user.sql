create database test;
use test;
create table if not exists user (
    id int auto_increment primary key,
    name varchar(20)
);