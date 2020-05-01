let useInput = initial => {
  let (value, setValue) = React.useState(() => initial);
  let setFormValue = evt => evt->ReactEvent.Form.target##value->setValue;
  (value, setFormValue);
};
