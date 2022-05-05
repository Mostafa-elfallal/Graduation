function x_c(dev,~)
     persistent fends;
     if isempty(fends)
         fends = 1;
     end
     if fends < 2
         fends = fends+1;
     else
         fends = 1;
         z = read(dev,dev.NumBytesAvailable,"uint8");
         disp((z));
     end
end