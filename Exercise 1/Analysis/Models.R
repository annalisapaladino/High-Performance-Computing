# read fixsize_bcast1_core_thin.csv

library(ggplot2)
library(dplyr)
library(tidyr)

# BCAST

bcast1 <- read.csv("fixsize_bcast1_core_thin.csv")

plot(bcast1$Processes, bcast1$Latency, pch =  19, xlab = "Processes", ylab = "Latency", cex = 1.5, cex.axis = 2, cex.lab=2)


poli_1<-lm(Latency ~ poly(Processes,1, raw=TRUE),data=bcast1)
pred_poli_1<-predict(poli_1, newdata=bcast1)
lines(bcast1$Processes,pred_poli_1,col="red", lwd=2)

summary(poli_1)
# latency = -0.233587 + 0.117043 * processes -> (bcast 1 lineare)

bcast2 <- read.csv("fixsize_bcast2_core_thin.csv")

plot(bcast2$Processes, bcast2$Latency, pch =  19, xlab = "Processes", ylab = "Latency", cex = 1.5, cex.axis = 2, cex.lab=2)


poli_2<-lm(Latency ~ poly(Processes,1, raw=TRUE),data=bcast2)
pred_poli_2<-predict(poli_2, newdata=bcast2)
lines(bcast2$Processes,pred_poli_2,col="red", lwd=2)

summary(poli_2)

# latency = -0.214384 + 0.109159 * processes-> (bcast 2 lineare)

bcast4 <- read.csv("fixsize_bcast4_core_thin.csv")

plot(bcast4$Processes, bcast4$Latency, pch =  19, xlab = "Processes", ylab = "Latency", cex = 1.5, cex.axis = 2, cex.lab=2)


poli_4<-lm(Latency ~ poly(Processes,2, raw=TRUE),data=bcast4)
pred_poli_4<-predict(poli_4, newdata=bcast4)
lines(bcast4$Processes,pred_poli_4,col="red", lwd=2)

summary(poli_4)
plot(poli_4)

# latency = -0.1586611  + 0.1543641 * processes - 0.0013735 * processe^2 -> (bcast 2 lineare)

# SCATTER

scatter1 <- read.csv("fixsize_scatter1_core_thin.csv")

plot(scatter1$Processes, scatter1$Latency, pch =  19, xlab = "Processes", ylab = "Latency", cex = 1.5, cex.axis = 2, cex.lab=2)


poli_s1<-lm(Latency ~ poly(Processes,1, raw=TRUE),data=scatter1)
pred_poli_s1<-predict(poli_s1, newdata=scatter1)
lines(scatter1$Processes,pred_poli_s1,col="red", lwd=2)

summary(poli_s1)

# latency = -0.215616 + 0.124241 * processes -> (scatter 1 lineare)

scatter2 <- read.csv("fixsize_scatter2_core_thin.csv")

plot(scatter2$Processes, scatter2$Latency, pch =  19, xlab = "Processes", ylab = "Latency", cex = 1.5, cex.axis = 2, cex.lab=2)


poli_s2<-lm(Latency ~ poly(Processes,1, raw=TRUE),data=scatter2)
pred_poli_s2<-predict(poli_s2, newdata=scatter2)
lines(scatter2$Processes,pred_poli_s2,col="red", lwd=2)

summary(poli_s2)

# latency = 0.141486 + 0.077624 * processes

scatter3 <- read.csv("fixsize_scatter3_core_thin.csv")

plot(scatter3$Processes, scatter3$Latency, pch =  19, xlab = "Processes", ylab = "Latency", cex = 1.5, cex.axis = 2, cex.lab=2)


poli_s3<-lm(Latency ~ poly(Processes,1, raw=TRUE),data=scatter3)
pred_poli_s3<-predict(poli_s3, newdata=scatter3)
lines(scatter3$Processes,pred_poli_s3,col="red", lwd=2)

summary(poli_s3)

# latency = -0.278261 + 0.120580 * processes



