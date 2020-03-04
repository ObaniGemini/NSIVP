# Codestyle


- 1 : Prefer camelCase for your functions and variables
- 2 : Spaces between fields, not when it's useless

```
void publicFunction( int X, size_t Y ) {
	for( int i = 0; i < X; i++ ) {
		printf( "%d", Y-- );
	}
} //This function is totally pointless
```

- 3 : Prefer
```
if( cond ) {
	...
}
```
to
```
if( cond )
{
	...
}
```
( there's no specific reason for that )

- 4 : Jump multiple lines between functions, and in functions between your blocks
- 5 : Don't name functions/vars following SIVP standards, we're not SIVP, we can have proper namings
- 6 : Don't write useless and/or ugly shit