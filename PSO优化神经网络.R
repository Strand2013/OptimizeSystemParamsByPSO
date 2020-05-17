library(nnet)
scale01=function(x){
  ncol=dim(x)[2]
  nrow=dim(x)[1]
  new=matrix(0,nrow,ncol)
  for(i in 1:ncol){
    max=max(x[,i])
    min=min(x[,i])
    for(j in 1:nrow)
      new[j,i]=(x[j,i]-min)/(max-min)
  }
  return(new)
}
load('white_wine.RData')
wine=w
names(wine)=c("fixedacidity","volatileacidity","citricacid","residualsugar","chlorides","freesulfurdioxide","totalsulfurdioxide","density","PH","sulphates","alcohol","quality")
cha=0
for(i in 1:4898){
  if(wine[i,12]>6)cha[i]="good"
  else if(wine[i,12]>5)cha[i]="mid"
  else cha[i]="bad"
}
wine[,12]=factor(cha)
str(wine)
set.seed(1123)
samp=sample(1:4898,3000)
wine[samp,1:11]=scale01(wine[samp,-12])
r=1/max(abs(wine[samp,1:11]))
set.seed(1012)
model1=nnet(quality~.,data=wine,subset=samp,size=4,rang=r,decay=5e-4,maxit=200)
model1$wts
summary(model1)
names(model1)
length(model1$terms)
model1$convergence # 是否达到最大迭代次数 1-达到 0-没达到,If get the max number of iteration It can not be the best model.
x_wine=wine[,1:11]
pred=predict(model1,x_wine,type="class") # The parameter of type is essential
true=wine[,12]
table(pred,true)
sum(pred!=true)/length(true)




# 速度更新参数
c1=1.4955
c2=1.4955
maxgen=100  # 迭代次数
sizepop=20  # 种群规模
popmax=1;popmin=-1  # 个体最大值与最小值 (输入适应度函数的自变量值)
vmax=1;vmin=-1      # 速度最大值与最小值
# 随机初始化粒子的位置和速度
pop<-matrix(0,20,63) # 计算一下神经网络模型的节点数 输入点*隐藏点+隐藏点+隐藏点*输出点+输出点=63
v<-matrix(0,20,63)
x<-c(rep(1,63))      # 初始的结点值
fitness<-c(rep(0,20))
##适应度函数
model1=nnet(quality~.,data=wine,subset=samp,size=4,rang=r,decay=5e-4,maxit=200)
fun<-function(x)
{
  mse=sum((predict(nnet(quality~.,data=wine,subset=samp,size=4,Wts=x[1:63],decay=0.001,maxit=100),wine[,1:11],type="class")!=true))/length(true)
  mse
}

##测试适应度函数
x=runif(63,-1,1)
mse=sum((predict(nnet(quality~.,data=wine,subset=samp,size=4,Wts=x[1:63],decay=0.001,maxit=100),wine[,1:11],type="class")!=true))/length(true)
mse
##种群初始化 
for(i in 1:sizepop)
{
  pop[i,]=runif(63,-1,1)
  v[i,]=(runif(63,-1,1))
  fitness[i]=fun(pop[i,])
}
pop[1,]
v[1,]

##寻找初始极值

bestfitness=min(fitness)      #  此处可以定义最优目标解 也可用max求最大值
which(fitness==min(fitness))
zbest=pop[17,] # 群体极值
zbest
gbest=pop      # 个体极值
gbest
fitnessgbest=fitness
fitnesszbest=bestfitness

##迭代寻优
yy=c(rep(0,100))   # 100次迭代
runif(1)
for(i in 1:maxgen)
{
  for(j in 1:sizepop)
  {
    v[j,]=v[j,]+c1*runif(1)*(gbest[j,]-pop[j,])+c2*runif(1)*(zbest-pop[j,])
    v[j,which(v[j,]>vmax)]=vmax
    v[j,which(v[j,]<vmin)]=vmin
    pop[j,]=pop[j,]+0.5*v[j,]
    pop[j,which(pop[j,]>popmax)]=popmax
    pop[j,which(pop[j,]<popmin)]=popmin
    fitness[j]=fun(pop[j,])
  }
  for(j in 1:sizepop)
  {
    if(fitness[j]<fitnessgbest[j])
    {
      gbest[j,]=pop[j,]
      fitnessgbest[j]=fitness[j]
    }
    if(fitness[j]<fitnesszbest)
    {
      zbest=pop[j,]
      fitnesszbest=fitness[j]
    }
  }
  yy[i]=fitnesszbest
}

yy#最优适应度值
zbest#最优适应度值对应的位置
plot(yy,type="b",main="最优个体适应度",xlab="进化代数",ylab="适应度")
min(yy)
model1=nnet(quality~.,data=wine,subset=samp,size=4,rang=r,Wts = zbest,decay=0.001,maxit=100)
p=predict(model1,x_wine,type="class")
sum(p!=true)/length(true)
#



























































# 0-1 standard data
scale<-function(x){
  ncol<-dim(x)[2]
  nrow<-dim(x)[1]
  new<-matrix(0,nrow,ncol)
  for(i in 1:ncol)
  {
    max<-max(x[,i])
    min<-min(x[,i])
    for(j in 1:nrow)
    {
      new[j,i]<-(x[j,i]-min)/(max-min)
    }
  }
  new
}
# 数据准备
data<-read.csv("D://data1.csv")
dim(data)
names(data)
data1<-data[,(2:5)]
head(data1)
data1[92,]
library(e1071)
library(nnet)
traindatax<-data1[c(1:18,24:41,47:64,70:87),1:3]
traindatay<-data1[c(1:18,24:41,47:64,70:87),4]

xundatax<-data1[c(19:23,42:46,65:69,88:92),1:3]
xundatay<-data1[c(19:23,42:46,65:69,88:92),4]

shiji<-data1[c(19:23,42:46,65:69,88:92),4]
shiji
head(traindatax)
# 训练集的y值
ty<-(traindatay-min(traindatay))/(max(traindatay)-min(traindatay))
ty
xx<-scale(xundatax)
# build the model of nnet
model<-nnet(scale(traindatax),ty,size=7,decay=0.001, maxit=100)
summary(model)
# prediction
pred<-predict(model,xx)
pred
pred<-pred*(max(shiji)-min(shiji))+min(shiji)
pred
shiji
acc<-1-sum((abs(pred[1:20]-shiji))/abs(shiji))/19
mse<-sum((pred[1:20]-shiji)^2)/length(pred)
mse
acc

####pso优化神经网络####
# 速度更新参数
c1=1.4955
c2=1.4955
maxgen=100  # 迭代次数
sizepop=20  # 种群规模
popmax=1;popmin=-1 # 个体最大值与最小值 (对适应度的函数结果而言)
vmax=1;vmin=-1     # 速度最大值与最小值
# 随机初始化粒子的位置和速度
pop<-matrix(0,20,41)
v<-matrix(0,20,41)
x<-c(rep(1,26),rep(0.5,11))
x[1:41]
shiji1<-(shiji-min(shiji))/(max(shiji)-min(shiji))
fitness<-c(rep(0,20))
##适应度函数
fun<-function(x)
{
  mse=(sum((predict(nnet(tx,ty,size=8,Wts=x[1:41],decay=0.001,maxit=100),xx)[1:20]-shiji1)^2))/20 
  mse
}

##种群初始化
x=runif(41,-1,1)
mse=(sum((predict(nnet(tx,ty,size=8,Wts=x,decay=0.001,maxit=100),xx)[1:20]-shiji)^2))/20 
mse

for(i in 1:sizepop)
{
  pop[i,]=runif(41,-1,1)
  v[i,]=(runif(41,-1,1))
  fitness[i]=fun(pop[i,])
}
pop[1,]
v[1,]

##寻找初始极值

bestfitness=min(fitness)
which(fitness==min(fitness))
zbest=pop[5,]
zbest
gbest=pop
gbest
fitnessgbest=fitness
fitnesszbest=bestfitness

##迭代寻优
yy=c(rep(0,100))
runif(1)
for(i in 1:maxgen)
{
  for(j in 1:sizepop)
  {
    v[j,]=v[j,]+c1*runif(1)*(gbest[j,]-pop[j,])+c2*runif(1)*(zbest-pop[j,])
    v[j,which(v[j,]>vmax)]=vmax
    v[j,which(v[j,]<vmin)]=vmin
    pop[j,]=pop[j,]+0.5*v[j,]
    pop[j,which(pop[j,]>popmax)]=popmax
    pop[j,which(pop[j,]<popmin)]=popmin
    fitness[j]=fun(pop[j,])
  }
  for(j in 1:sizepop)
  {
    if(fitness[j]<fitnessgbest[j])
    {
      gbest[j,]=pop[j,]
      fitnessgbest[j]=fitness[j]
    }
    if(fitness[j]<fitnesszbest)
    {
      zbest=pop[j,]
      fitnesszbest=fitness[j]
    }
  }
  yy[i]=fitnesszbest
}

yy#最优适应度值
zbest#最优适应度值对应的位置
plot(yy,type="l",main="最优个体适应度",xlab="进化代数",ylab="适应度")

model<-nnet(tx,ty,size=8,Wts=zbest,decay=0.001,maxit=100)
pred<-predict(model,xx)
pred<-pred*(max(shiji)-min(shiji))+min(shiji)
pred
acc<-1-sum((abs(pred[1:20]-shiji))/abs(shiji))/19
acc
mse=sum((pred[1:20]-shiji)^2)/length(pred)
mse

pred=read.csv("D://pred.csv")
pred


liuyu=read.csv("D://datau.csv")
head(liuyu)
y1<-liuyu[,2]
jibie<-NA
jibie[which(y1<=(-0.8))]="1"
jibie[which(y1>-0.8&y1<=-0.4)]="2"
jibie[which(y1>-0.4&y1<=0)]="3"
jibie[which(y1>0&y1<=0.4)]="4"
jibie[which(y1>0.4&y1<=0.8)]="5"
jibie[which(y1>0.8&y1<=1)]="6"
data=liuyu
data[,4]=jibie
data
write.csv(data,"D://pred2.csv")