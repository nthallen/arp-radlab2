function pradenvcp(varargin);
% pradenvcp( [...] );
% Chamber P
h = timeplot({'InstP','ChamberP','ChambP'}, ...
      'Chamber P', ...
      'P', ...
      {'InstP','ChamberP','ChambP'}, ...
      varargin{:} );
