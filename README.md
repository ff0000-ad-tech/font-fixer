##### RED Interactive Agency - Ad Technology

font-fixer
===============

This package utilizes a publically available C program that removes DRM from `.ttf` fonts. It is utilized for brand-owned fonts that need to serve in-banner. In all cases, the font has been reduced from its full set of glyphs to only the characters that are required for that ad unit to run. Furthermore, RED Ad Tech repackages the remaining glyphs in our binary asset packer, making the compromised font essentially unusable for any other purposes.

### **Warning**: Usage of this package on fonts which you are not licensed to distribute is illegal!

## CLI
`npm run fix ./path/to/font/asset`
