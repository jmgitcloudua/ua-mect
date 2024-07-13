const register_email = document.getElementById('email');
const register_password = document.getElementById('password');
const register_button = document.getElementById('btn-submit');

const cek_reg_email = localStorage.getItem('register_email')
const cek_reg_password = localStorage.getItem('register_password')
const cek_log_email = localStorage.getItem('login_email')
const cek_log_password = localStorage.getItem('login_password')

if (cek_reg_email, cek_reg_password, cek_log_email, cek_log_password != null) {
    window.location = 'account.html'
}

register_button.addEventListener('click', function () {

    const valid_email = localStorage.getItem('register_email')
    const valid_password = localStorage.getItem('register_password')

    if (register_email.value === valid_email || register_password.value === valid_password) {
        alert('Sua conta foi ativada! Faça Login agora!!')
        return false
    }

    if (register_email.value, register_password.value === '') {
        alert('Dados inválidos ❌')
        localStorage.removeItem('register_email')
        localStorage.removeItem('register_password')
        return false
    } else {
        localStorage.setItem('register_email', register_email.value)
        localStorage.setItem('register_password', register_password.value)
        alert('Registo efetuado com sucesso ✅')
        window.location = 'login.html'
    }

})