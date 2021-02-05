-- leetcode 题解

-- 第二高薪水
select (select distinct Salary 
from Employee 
order by Salary desc
limit 1,1) as SecondHighestSalary;

-- 此题是第二是根据数值，所以 distinct
-- null 处理： select null 返回 null
-- order by ... limit m, n 表示 跳过 m 个后的连续 n 个
-----------------------------------------------------------

-- 第 N 高薪水
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
set N = N-1;
  RETURN (
      # Write your MySQL query statement below.
      select (
      select distinct Salary from Employee
      order by Salary desc
      limit N,1
      ) as theNthHighestSalary
      
  );
END

-- limit 后面不能根 N-1 之类的表达式
-- select ( select ... ) as xxx  加表头同时 null 也能正常返回
--------------------------------------------------------------------

-- 生成排名
select Score, ( select count(distinct score) from Scores where score >= s.score ) as "Rank"
from Scores as s
order by Score desc;
-- 该题是在原有表的基础上生成一个排名的字段
-- 用一个子查询 产生 rank，原理统计出分数比我高的记录的个数
-- 或者用窗口函数：
select Score, dense_rank() over (order by Score desc) as "Rank" from Scores;
----------------------------------------------------------------------------

-- 185. 部门工资前三高的所有员工（分部门统计，一起返回）
select d.Name as Department, e.Name as Employee, e.Salary as Salary from Employee as e join Department as d on e.DepartmentId=d.Id 
where (
    select count(distinct e2.Salary) from Employee as e2 where e2.Salary > e.Salary and e.DepartmentId=e2.DepartmentId
) < 3

-- 首先拼接得到表的全集，然后关键在于如何分部门筛选出前三高
-- 条件是排名限制，所以想办法生成每个部门的排名！与分数排名类似, 同样用 子查询比较计数 得到排名
-- 排名是仅仅根据工资数值，不在乎人头数，排名计数要加 "distinct"
----------------------------------------------------------------------------------------
