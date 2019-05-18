const f = (n)=>{
  if (n<=1){
    return 1;
  } else {
    return f(n-1)+f(n-2);
  }
}

console.log( f(+process.argv[2]) );