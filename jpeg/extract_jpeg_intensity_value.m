img=imread('ncku.jpg');
fp = fopen('ncku.txt','w');
for n=1:3
    for y=1:540
        for x=1:826
            fprintf(fp,'%d, ',img(y,x,n));
            disp(img(y,x,n))
        end
    end
end