1 如果出现报错Error connecting to agent: Connection refused 说明 ssh-agent 服务根本没在运行。

ssh -T 能通，是因为它直接读取 ~/.ssh/id_rsa 密钥文件，绕过了 ssh-agent。但 Git 默认会尝试通过 ssh-agent 来获取密钥，而 agent 没启动，所以就卡住了。

2 解决方法：启动 ssh-agent 并加载密钥
2.1 eval $(ssh-agent)
Agent pid 12345

2.2 ssh-add ~/.ssh/id_rsa

2.3 git push origin dev