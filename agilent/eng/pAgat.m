function pAgat(varargin);
% pAgat( [...] );
% Agilent Temp
h = timeplot({'RefT'}, ...
      'Agilent Temp', ...
      'Temp', ...
      {'RefT'}, ...
      varargin{:} );
