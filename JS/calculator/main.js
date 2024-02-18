function div(x, y)
{
  return x / y;
}

function multi(x, y)
{
  return x * y;
}

function soma(x, y)
{
  return x + y;
}


function sub(x, y)
{
  return x - y;
}


function main()
{
  let x = 5, y = 10;
  let choice = 3;

  console.log("Escolha uma opção: ");
  console.log("1. Adição\n2. Subtração\n3. Multiplicação\n4. Divisão");
  console.log("Insira os valores para a operação: ");
  // console.log("x = ");
  // console.log("y = "); 


  switch (choice) {
    case 1:
      console.log(`x = ${x}, y = ${y} | resultado = ${soma(x, y)}`);
      break;
    
    case 2:
      console.log(`x = ${x}, y = ${y} | resultado = ${sub(x, y)}`);
      break;

    case 3:
      console.log(`x = ${x}, y = ${y} | resultado = ${multi(x, y)}`);
      break;

    case 4:
      console.log(`x = ${x}, y = ${y} | resultado = ${div(x, y)}`);
      break;

    default:
      break;
  }
}

main();
