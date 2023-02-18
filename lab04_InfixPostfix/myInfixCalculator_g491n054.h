#ifndef MYINFIXCALCULATOR
#define MYINFIXCALCULATOR

#include <string>
#include <vector>
#include "myStack_g491n054.h"

class myInfixCalculator
{
public:
  myInfixCalculator( )
  { }

  ~myInfixCalculator( )
  { }

  void tokenize( const std::string & s, std::vector<std::string> &tokens )
  {
    std::string numeric = "";

    for( unsigned int i = 0; i < s.length(); i++ )
    {
      if( s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' )
      {
        if( !numeric.empty( ) )
        {
          tokens.push_back( numeric );
          numeric = "";
        }
        std::string operators = "";
        operators = operators + s[i];
        tokens.push_back( operators );
      }
      else
      {
        numeric = numeric + s[i];
        if( i == s.length( ) - 1 )
        {
          tokens.push_back( numeric );
          numeric = "";
        }
      }
    }
  }

  bool isOperator( std::string & s )
  {
    if( s == "(" || s == ")" || s == "*" || s == "/" || s == "+" || s == "-" )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool isNumeric( std::string & s )
  {
    if( !isOperator( s ) )
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  int priority( char ch )
  {
    if( ch == '+' || ch == '-' )
    {
      return 1;
    }
    else if( ch == '*' || ch == '/' )
    {
      return 2;
    }
    else
    {
      return 0;
    }
  }

  std::string infixToPostfix( const std::string & s )
  {
    myStack<char> operStack( 0 );
    std::string numeric = "";
    std::string postfix = "";

    for( unsigned int i = 0; i < s.size(); i++ )
    {
      if( s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' )
      {
        if( !numeric.empty( ) )
        {
          postfix.append( numeric );
          postfix.append( " " );
          numeric = "";
        }
        if( s[i] == '(' )
        {
          operStack.push( '(' );
        }
        else if( s[i] == ')' )
        {
          while( !operStack.empty( ) && operStack.top( ) != '(' )
          {
            char temp = operStack.top( );
            postfix += temp;
            postfix.append( " " );
            operStack.pop( );
          }
          operStack.pop( );
        }
        else
        {
          if( priority( s[i] ) > priority( operStack.top( ) ) )
          {
            operStack.push( s[i] );
          }
          else
          {
            while( !operStack.empty( ) && priority( s[i] ) <= priority( operStack.top( ) ) )
            {
              postfix += operStack.top( );
              postfix.append( " " );
              operStack.pop( );
            }
            operStack.push( s[i] );
          }
        }
      }
      else
      {
        numeric = numeric + s[i];
        if( i == s.length( ) - 1 )
        {
          postfix.append( numeric );
          postfix.append( " " );
          numeric = "";
        }
      }
    }

    while( !operStack.empty( ) )
    {
      postfix += operStack.top( );
      postfix.append( " " );
      operStack.pop( );
    }

    return postfix;
  }

  double calculatePostfix( const std::string & s )
  {
    myStack<double> numStack( 0 );
    double temp = 0.0;
    std::string numeric = "";

    for( unsigned int i = 0; i < s.length( ); i++ )
    {
      if( s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' )
      {
        double num1 = numStack.top( );
        numStack.pop( );
        double num2 = numStack.top( );
        numStack.pop( );

        if( s[i] == '+' )
        {
          numStack.push( num2 + num1 );
        }
        else if( s[i] == '-' )
        {
          numStack.push( num2 - num1 );
        }
        else if( s[i] == '*' )
        {
          numStack.push( num2 * num1 );
        }
        else if( s[i] == '/' )
        {
          numStack.push( num2 / num1 );
        }
      }
      else
      {
        if( s[i] == ' ' && !numeric.empty( ) )
        {
          temp = std::stod( numeric );
          numStack.push( temp );
          numeric = "";
        }
        else if( s[i] != ' ' )
        {
          numeric = numeric + s[i];
        }
        else
        {
          continue;
        }
      }
    }

    return numStack.top( );
  }
};

#endif
