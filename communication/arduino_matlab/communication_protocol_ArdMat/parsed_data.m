load("excell_modified.txt")

excell_modified;

volt = excell_modified(:,1);
angle = excell_modified(:,2) *pi/180;
tstamp = excell_modified(:,3);

eoi = find(volt==-1);

n = length(eoi);

start = 0;
for i=1:n
    svolt(i,1) = mean(volt(start+1:eoi(i)-1))/255;
    sspeed(i,1) = (angle(eoi(i)-1)-angle(start+1))*(pi/180)/((tstamp(eoi(i)-1)-tstamp(start+1))/1000);
    start = eoi(i);
end    
plot(svolt,sspeed)
