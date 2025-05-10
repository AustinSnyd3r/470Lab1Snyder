# Get the date, and format to only be date and time.
cDate=$(date +"%Y-%m-%d_%H-%M")

# Save the prefix for the subdirectories
dirPrefix="file"

# Save the prefix for the files within subdirs
filePrefix="tuser"

# Use an array of 10 langs to put in the files.
langs=("Java" "Python" "C" "Go" "Rust" "Perl" "ML" "Kotlin" "PHP" "C++")

# Loop to make all the subdirectories (with right number for name). 
for i in {101..110}; do
  # Save the full path to use later.
  fullPath="$cDate/$dirPrefix$i"
  
  # Use -p to either make parent and then a subdirectory, or if parent exists just the child dir.
  mkdir -p "$fullPath"
  
  # Loop for making files in the subdirectory.
  for j in {501..510}; do
    # Echo to make a file with the language in it as text. 
    echo ${langs[j-501]} > $fullPath/$filePrefix$j.txt
  done 
done

