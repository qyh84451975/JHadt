## 创建空仓库
git init
## 将readme.md文本文件添加到仓库
git add readme.md
## 将刚添加的文件提交到仓库
git cm -m "wrote a readme file."
## 查看文件修改内容
git diff readme.md
## 查看日志
git log
## 单行显示日志
git log --oneline
## 查看以往命令
git reflog
## 回滚到指定分支
git reset --hard f32534c
## 回滚到上个分支
git reset --hard HEAD^
git reset --hard HEAD^^
git reset --hard HEAD~3
## 查看日志统计信息
git log --stat
## 带注释的日志输出
git log -p #(--patch)
## 只显示一个commit
git show
git show f32534c
## 撤销修改
git co -- file
1.file自修改后还没有被放到暂存区，现在撤销就回到了喝版本库一模一样的状态
2.file已经添加到了暂存区，又做了修改，现在撤销就回到添加到暂存区后的状态
总之，就是让这个文件回到最近一次cm或者add的状态
## 将暂存区文件回退到工作区
git reset HEAD <file>
## 删除版本库中的文件
git rm file
## 恢复删除
git co -- file
## 将本地库关联远程库
git remote add origin https://github.com/kaffeeJ/gitstudy.git
## 将本地内容推送到远程库
git push
git pull origin Enterprise/Feature_1.0.0:qjgit push -u origin master
## 将远程某分支拉到本地某分支，如果没有则创建
git pull origin Enterprise/Feature_1.0.0:qj
## 查看分支合并图
git log --graph
## 禁用Fast forward合并
## 本次合并会创建一个新commit，所以加上-m
git mg --no-ff -m "merge with no-ff" dev
## 修改bug，当dev分支修改的内容暂时无法提交时，可以使用git stash暂存现场，当bug修复完成，恢复现场。
git stash
git stash pop
git cherry-pick <commit>
## 拉取远程指定分支
git co -b dev origin/dev
## 查看历史提交
git log --oneline --abbrev-commit
## 在某个commit上打分支
git tag v1.0 f52c633
git tag -a v1.0 -m "doc for tag" f52c633
## 删除本地标签
git tag -d v1.0
## 推送本地标签到远程
git push origin v1.0
## 推送所有未推送的标签到远程
git push origin --tags
## 如果tag已经上传到远程,先删除本地tag，再push去删除远程
git tag -d v1.0
git push origin :refs/tags/v1.0


