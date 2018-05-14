
py_file="/Users/naxin/Documents/THU/大二下/计算思维与系统设计基础/nand2tetris/projects/JackCompiler/JackCompiler.py"
function getdir(){
	i=0
    for element in `ls $1`
    do
    	python3 ${py_file} $1/${element}
    	echo "done "$i
    	i=`expr $i + 1`
    done
}
root_dir="/Users/naxin/Documents/THU/大二下/计算思维与系统设计基础/nand2tetris/projects/11"
getdir $root_dir